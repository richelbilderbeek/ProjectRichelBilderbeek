#include <cassert>
#include <cstdio>
#include <memory>

//THIS PROGRAM MIGHT CAUSE A RUNTIME CRASH
//IT PROBABLY CORRUPTS SOME MEMORY
//DO NOT RUN IT!
//
//Sadly, I cannot remember why this was so...
int main()
{
  //Create a file to write to
  const std::unique_ptr<FILE> my_file(std::fopen("my_file.txt","w"));
  //Assume the file is created successfully
  assert(my_file);
  //Put text at the start of the file
  std::fputs("Bilderbickel",my_file.get());
  //Go to the 9th position
  std::fseek(my_file.get(),9,SEEK_SET );
  //Put text at the 9th position
  std::fputs ("k",my_file.get());
  //Close the file
  std::fclose (my_file.get());
}
