/*! \include diploid.cc
  Simulate a single, finite Wright-Fisher diploid population with mutation, recombination, and no selection.

  This program illustrates many features of fwdpp:
  1.  Custom mutation classes
  2.  Implementing a mutation model (infinitely-many sites)
  3.  Iterating a population through its life cycle
  4.  Outputting a sample in "ms" format
 */

#include <fwdpp/diploid.hh>
#include <Sequence/SimData.hpp>

/*
  We define a new mutation type, derived from the base class KTfwd::mutation_base.
  This type adds a selection coefficient (s), dominance coefficient (h),
  and the generation when the mutation first appeared in the population (g)
 */
struct mutation_with_age : public KTfwd::mutation_base
{
  unsigned g;
  double s,h;
  /*
    The constructor initializes all class data, including that of the base class via a constructor
    call to the base class.
   */
  mutation_with_age(const unsigned & __o,const double & position, const unsigned & count, const bool & isneutral = true)
    : KTfwd::mutation_base(position,count,isneutral),g(__o),s(0.),h(0.)
  {	
  }
};

//Simplify our lives a bit with typedefs

/*
  NOTE: we are using boost containers with boost memory allocators.  
  My experience on my systems is that each of those objects is worth a 5-10% 
  run time speedup compare to the same objects from namespace std.

  fwdpp is compatible with ANY container system as long as the
  one containing gametes conforms to the behavior of std::vector and 
  the one containing mutations conforms to the behavior of std::list 
  (especially w/regards to no pointer invalidation upon insertion/delete!!)
*/

//compiling the code with -DUSE_STANDARD_CONTAINERS will use std::vector and std::list instead of the boost alternatives
typedef mutation_with_age mtype;
#include <common_gamete.hpp>

/*
  This function generates neutral mutations under the infinitely-many sites assumption
 */
mutation_with_age neutral_mutations_inf_sites(gsl_rng * r,const unsigned & generation,mlist * mutations,
					      lookup_table_type * lookup)
{
  //Generate new mutation position on the interval [0,1)
  double pos = gsl_rng_uniform(r);
  /*
    An alternative implementation of the while loop below would be:
    while( std::find_if( mutations->begin(),mutations->end(),std::bind(KTfwd::mutation_at_pos(),std::placeholders::_1,pos) != mutations->end()) )
    {
      pos = gsl_rng_uniform(r);
    }

    However, that operation is typically much slower, esp. as the mutation rate gets higher
   */
  while( lookup->find(pos) != lookup->end() ) //make sure it doesn't exist in the population
    { 
      pos = gsl_rng_uniform(r);  //if it does, generate a new one
    }
  //update the lookup table
  lookup->insert(pos);

  /*
    The program will abort if the following conditions are true:
    1.  The mutation position that we generated does indeed exist in the population (implying that our hashing scheme has failed).
    2.  AND, the program was NOT compiled with -DNDEBUG

    fwdpp makes extensive internal use of the C-language assert macro (#include <cassert>).  The macro is enabled if a program is 
    compiled like this:
    c++ -o program program.cc

    It is disabled if a program is compiled like this:
    c++ -DNDEBUG program program.cc

    Thus, a programmer may make use of the preprocessor macro NDEBUG to write detailed debugging routines that are easily disabled.
    
    For example:
    #ifndef NDEBUG
    bool condition = false;
    //do some complex checking of your data here.  If all is okay, set condition = true;
    #endif
    assert( condition == true );

    That check may be expensive at run-time, but is easily disabled by recompiling using -DNDEBUG

    An example of such a debugging routine is KTfwd::check_sum
   */
  assert(std::find_if(mutations->begin(),mutations->end(),std::bind(KTfwd::mutation_at_pos(),std::placeholders::_1,pos)) == mutations->end());

  //return constructor call to mutation type
  return mutation_with_age(generation,pos,1,true);
}
 
int main(int argc, char ** argv)
{
  if (argc != 8)
    {
      std::cerr << "Too few arguments\n"
		<< "Usage: diploid N theta rho ngens samplesize nreps seed\n";
      exit(10);
    } 
  int argument=1;
  const unsigned N = atoi(argv[argument++]);           //Number of diploids
  const double theta = atof(argv[argument++]);         //4*n*mutation rate.  Note: mutation rate is per REGION, not SITE!!
  const double rho = atof(argv[argument++]);           //4*n*recombination rate.  Note: recombination rate is per REGION, not SITE!!
  const unsigned ngens = atoi(argv[argument++]);       //Number of generations to simulate
  const unsigned samplesize1 = atoi(argv[argument++]); //Sample size to draw from the population
  int nreps = atoi(argv[argument++]);                  //Number of replicates to simulate
  const unsigned seed = atoi(argv[argument++]);        //Random number seed

  const double mu = theta/double(4*N);                 //per-gamete mutation rate
  
  /*
    littler r is the recombination rate per region per generation.

    Typically, given the above definition of rho, this should be rho/(4*N).

    However, the implementation of KTfwd::recombine treats littler as
    per gamete rather than per-diploid.  

    This is a bit weird, but is transparent to any users of this program,
    and is just an internal detail.
   */
  const double littler = rho/double(8*N);
  
  //Write the command line to stderr
  std::copy(argv,argv+argc,std::ostream_iterator<char*>(std::cerr," "));
  std::cerr << '\n';
  
  //Initiate random number generation system
  gsl_rng * r =  gsl_rng_alloc(gsl_rng_ranlxs2);
  gsl_rng_set(r,seed);

  unsigned twoN = 2*N;

  while(nreps--)
    {
      //the population begins with 1 gamete with no mutations amd initial count 2N
      gvector gametes(1,gtype(twoN));
      gametes.reserve(twoN);
      mlist mutations;  //the population is devoid of mutations
      std::vector<mtype> fixations;  //store mutation that fix.  Passed to KTfwd::remove_fixed_lost
      std::vector<unsigned> fixation_times; //store when they fix.  Passed to KTfwd::remove_fixed_lost
      unsigned generation;
      lookup_table_type lookup;  //this is our lookup table for the mutation model
      for( generation = 0; generation < ngens; ++generation )
	{
	  //Sample gamete frequencies proportional to fitness/(population mean fitness, aka wbar).  wbar is the return value
    KTfwd::sample_diploid(r,&gametes,twoN,
				       /*
					 Fitness is multiplicative over sites.

					 The fitness model takes two gametes as arguments.  
					 The gametes are passed to this function by 
					 KTfwd::sample_diploid, and the _1 and _2 are placeholders for
					 those gametes (see documentation for boost/bind.hpp for details).
					 The 2. means that fitnesses are 1, 1+sh, and 1+2s for genotypes
					 AA, Aa, and aa, respectively, where a is a mutation with
					 selection coefficient s and dominance h, and the fitness of 
					 the diploid is the product of fitness over sites

					 There is no selection in this simulation, but this
					 function is called anyways to illustrate it as multiplicative
					 models are very common in population genetics
				       */
				       std::bind(KTfwd::multiplicative_diploid(),std::placeholders::_1,std::placeholders::_2,2.), 
				       /*
					 For each gamete still extant afte sampling,
					 remove the pointers to any mutations that have 
					 been fixed or lost from the population.
					 
					 For more complex models such as quantitative
					 traits evolving towards an optimum, one may not
					 with to remove fixations.  In that case,
					 replace the line below with
					 std::bind(KTfwd::mutation_remover(),std::placeholders::_1,twoN));

					 Under multiplicative fitness and Wright-Fisher sampling
					 proportional to relative fitness, fixed mutations
					 are just a constant applied to everyone's fitness, so we 
					 can remove them, making the simulation faster, etc.
				       */
				       std::bind(KTfwd::mutation_remover(),std::placeholders::_1,0,twoN));       

	  /*
	    Clean up the mutation list to remove any mutations fixed or lost.

	    If you do not want to remove fixed mutations (in the case of models
	    where fixed mutations still matter, such as evolution towards an optimum), 
	    replace the line below with:
	    KTfwd::remove_lost(&mutations);
	  */
	  KTfwd::remove_fixed_lost(&mutations,&fixations,&fixation_times,&lookup,generation,twoN);
	  assert( lookup.size() == mutations.size() );

	  //if all is going well, the (sum of the counts of each gamete) == twoN, otherwise we have a problem and must abort.
	  assert(KTfwd::check_sum(gametes,twoN));



	  //Mutate the gamete pool
    KTfwd::mutate(r,&gametes,&mutations,mu,
					 /*
					   The mutation model (defined above) will pass each gamete
					   to be mutated to the mutation model function.  Again, _1
					   is used as a placeholder for that gamete.
					 */
					 std::bind(neutral_mutations_inf_sites,r,generation,std::placeholders::_1,&lookup),
					 /*
					   Policy telling KTfwd::mutate how to add mutated gametes into the gamete pool.
					   If mutation results in a new gamete, add that gamete to the 
					   end of gametes. This is always the case under infinitely-many sites,
					   but for other mutation models, mutation may result in a new
					   copy identical to an existing gamete.  If so,
					   that gamete's frequency increases by 1.
					  */
					 std::bind(KTfwd::push_at_end<gtype,gvector>,std::placeholders::_1,std::placeholders::_2),
					 /*
					   Policy to insert new mutations at the end of the mutations list
					 */
					 std::bind(KTfwd::insert_at_end<mtype,mlist>,std::placeholders::_1,std::placeholders::_2));
	  assert( lookup.size() == mutations.size() );
	  assert(KTfwd::check_sum(gametes,twoN));

	  //Recombination
	  //unsigned nrec = KTfwd::recombine_test_not_inserting_as_much(r, 
    KTfwd::recombine(r,
					   &gametes,
					   twoN, 
					   littler, 
					   //This is the genetic map: uniform along [0,1)
					   std::bind( gsl_rng_uniform,r ) );
	  assert(KTfwd::check_sum(gametes,twoN));
	}
      Sequence::SimData sdata;

      std::vector<std::pair<double,std::string> > mslike = KTfwd::ms_sample(r,gametes,samplesize1,twoN,true);

      if(!mslike.empty())
	{
	  sdata.assign(mslike.begin(),mslike.end());
	  std::cout << sdata << '\n';
	}
      else
	{
	  std::cout << "//\nsegsites: 0\n";
	}      
    }
}
