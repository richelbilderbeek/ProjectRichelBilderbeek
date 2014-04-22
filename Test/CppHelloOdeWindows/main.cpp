#define dSINGLE
//D:\Projects\Libraries\ode-0.12\include\ode\common.h

//From http://ode-wiki.org/wiki/index.php?title=HOWTO_simple_bouncing_sphere
#include <ode/ode.h>
#include <drawstuff/drawstuff.h>

// dynamics and collision objects
static dWorldID world;
static dSpaceID space;
static dBodyID body;
static dGeomID geom;
static dMass m;
static dJointGroupID contactgroup;

// this is called by dSpaceCollide when two objects in space are
// potentially colliding.
static void nearCallback (void *data, dGeomID o1, dGeomID o2)
{

    dBodyID b1 = dGeomGetBody(o1);
    dBodyID b2 = dGeomGetBody(o2);
    dContact contact;
    contact.surface.mode = dContactBounce | dContactSoftCFM;
    // friction parameter
    contact.surface.mu = dInfinity;
    // bounce is the amount of "bouncyness".
    contact.surface.bounce = 0.9;
    // bounce_vel is the minimum incoming velocity to cause a bounce
    contact.surface.bounce_vel = 0.1;
    // constraint force mixing parameter
    contact.surface.soft_cfm = 0.001;
    if (int numc = dCollide (o1,o2,1,&contact.geom,sizeof(dContact))) {
        dJointID c = dJointCreateContact (world,contactgroup,&contact);
        dJointAttach (c,b1,b2);
    }
}

// start simulation - set viewpoint
static void start()
{
    static float xyz[3] = {2.0f,-2.0f,1.7600f};
    static float hpr[3] = {140.000f,-17.0000f,0.0000f};
    dsSetViewpoint (xyz,hpr);
}

// simulation loop
static void simLoop (int pause)
{
    const dReal *pos;
    const dReal *R;
    // find collisions and add contact joints
    dSpaceCollide (space,0,&nearCallback);
    // step the simulation
    dWorldQuickStep (world,0.01);
    // remove all contact joints
    dJointGroupEmpty (contactgroup);
    // redraw sphere at new location
    pos = dGeomGetPosition (geom);
    R = dGeomGetRotation (geom);
    dsDrawSphere(pos,R,dGeomSphereGetRadius (geom));
}

int main (int argc, char **argv)
{
    // setup pointers to drawstuff callback functions
    dsFunctions fn;
    fn.version = DS_VERSION;
    fn.start = &start;
    fn.step = &simLoop;
    fn.stop = 0;
    fn.command = 0;
    fn.path_to_textures = "../../drawstuff/textures";

    dInitODE ();
    // create world
    world = dWorldCreate ();
    space = dHashSpaceCreate (0);
    dWorldSetGravity (world,0,0,-0.2);
    dWorldSetCFM (world,1e-5);
    dCreatePlane (space,0,0,1,0);
    contactgroup = dJointGroupCreate (0);
    // create object
    body = dBodyCreate (world);
    geom = dCreateSphere (space,0.5);
    dMassSetSphere (&m,1,0.5);
    dBodySetMass (body,&m);
    dGeomSetBody (geom,body);
    // set initial position
    dBodySetPosition (body,0,0,3);
    // run simulation
    dsSimulationLoop (argc,argv,352,288,&fn);
    // clean up
    dJointGroupDestroy (contactgroup);
    dSpaceDestroy (space);
    dWorldDestroy (world);
    dCloseODE();
}

/*

DEFINES += dDOUBLE
DEFINES += CCD_DOUBLE

HEADERS += \
    ../../Libraries/ode-0.12/ode/src/array.h \
    ../../Libraries/ode-0.12/ode/src/collision_kernel.h \
    ../../Libraries/ode-0.12/ode/src/collision_libccd.h \
    ../../Libraries/ode-0.12/ode/src/collision_space_internal.h \
    ../../Libraries/ode-0.12/ode/src/collision_std.h \
    ../../Libraries/ode-0.12/ode/src/collision_transform.h \
    ../../Libraries/ode-0.12/ode/src/collision_trimesh_colliders.h \
    ../../Libraries/ode-0.12/ode/src/collision_trimesh_internal.h \
    ../../Libraries/ode-0.12/ode/src/collision_util.h \
    ../../Libraries/ode-0.12/ode/src/config.h \
    ../../Libraries/ode-0.12/ode/src/heightfield.h \
    ../../Libraries/ode-0.12/ode/src/lcp.h \
    ../../Libraries/ode-0.12/ode/src/mat.h \
    ../../Libraries/ode-0.12/ode/src/objects.h \
    ../../Libraries/ode-0.12/ode/src/obstack.h \
    ../../Libraries/ode-0.12/ode/src/odeou.h \
    ../../Libraries/ode-0.12/ode/src/odetls.h \
    ../../Libraries/ode-0.12/ode/src/quickstep.h \
    ../../Libraries/ode-0.12/ode/src/step.h \
    ../../Libraries/ode-0.12/ode/src/util.h \
    ../../Libraries/ode-0.12/ode/src/joints/amotor.h \
    ../../Libraries/ode-0.12/ode/src/joints/ball.h \
    ../../Libraries/ode-0.12/ode/src/joints/contact.h \
    ../../Libraries/ode-0.12/ode/src/joints/fixed.h \
    ../../Libraries/ode-0.12/ode/src/joints/hinge.h \
    ../../Libraries/ode-0.12/ode/src/joints/hinge2.h \
    ../../Libraries/ode-0.12/ode/src/joints/joint.h \
    ../../Libraries/ode-0.12/ode/src/joints/joint_internal.h \
    ../../Libraries/ode-0.12/ode/src/joints/joints.h \
    ../../Libraries/ode-0.12/ode/src/joints/lmotor.h \
    ../../Libraries/ode-0.12/ode/src/joints/null.h \
    ../../Libraries/ode-0.12/ode/src/joints/piston.h \
    ../../Libraries/ode-0.12/ode/src/joints/plane2d.h \
    ../../Libraries/ode-0.12/ode/src/joints/pr.h \
    ../../Libraries/ode-0.12/ode/src/joints/pu.h \
    ../../Libraries/ode-0.12/ode/src/joints/slider.h \
    ../../Libraries/ode-0.12/ode/src/joints/universal.h \
    ../../Libraries/ode-0.12/ode/src/../../Include/drawstuff/drawstuff.h

SOURCES += \
    ../../Libraries/ode-0.12/ode/src/array.cpp \
    ../../Libraries/ode-0.12/ode/src/box.cpp \
    ../../Libraries/ode-0.12/ode/src/capsule.cpp \
    ../../Libraries/ode-0.12/ode/src/collision_cylinder_box.cpp \
    ../../Libraries/ode-0.12/ode/src/collision_cylinder_plane.cpp \
    ../../Libraries/ode-0.12/ode/src/collision_cylinder_sphere.cpp \
    ../../Libraries/ode-0.12/ode/src/collision_cylinder_trimesh.cpp \
    ../../Libraries/ode-0.12/ode/src/collision_kernel.cpp \
    ../../Libraries/ode-0.12/ode/src/collision_libccd.cpp \
    ../../Libraries/ode-0.12/ode/src/collision_quadtreespace.cpp \
    ../../Libraries/ode-0.12/ode/src/collision_sapspace.cpp \
    ../../Libraries/ode-0.12/ode/src/collision_space.cpp \
    ../../Libraries/ode-0.12/ode/src/collision_transform.cpp \
    ../../Libraries/ode-0.12/ode/src/collision_trimesh_box.cpp \
    ../../Libraries/ode-0.12/ode/src/collision_trimesh_ccylinder.cpp \
    ../../Libraries/ode-0.12/ode/src/collision_trimesh_disabled.cpp \
    ../../Libraries/ode-0.12/ode/src/collision_trimesh_distance.cpp \
    ../../Libraries/ode-0.12/ode/src/collision_trimesh_gimpact.cpp \
    ../../Libraries/ode-0.12/ode/src/collision_trimesh_opcode.cpp \
    ../../Libraries/ode-0.12/ode/src/collision_trimesh_plane.cpp \
    ../../Libraries/ode-0.12/ode/src/collision_trimesh_ray.cpp \
    ../../Libraries/ode-0.12/ode/src/collision_trimesh_sphere.cpp \
    ../../Libraries/ode-0.12/ode/src/collision_trimesh_trimesh.cpp \
    ../../Libraries/ode-0.12/ode/src/collision_trimesh_trimesh_new.cpp \
    ../../Libraries/ode-0.12/ode/src/collision_util.cpp \
    ../../Libraries/ode-0.12/ode/src/convex.cpp \
    ../../Libraries/ode-0.12/ode/src/cylinder.cpp \
    ../../Libraries/ode-0.12/ode/src/error.cpp \
    ../../Libraries/ode-0.12/ode/src/export-dif.cpp \
    ../../Libraries/ode-0.12/ode/src/fastdot.c \
    ../../Libraries/ode-0.12/ode/src/fastldlt.c \
    ../../Libraries/ode-0.12/ode/src/fastlsolve.c \
    ../../Libraries/ode-0.12/ode/src/fastltsolve.c \
    ../../Libraries/ode-0.12/ode/src/heightfield.cpp \
    ../../Libraries/ode-0.12/ode/src/lcp.cpp \
    ../../Libraries/ode-0.12/ode/src/mass.cpp \
    ../../Libraries/ode-0.12/ode/src/mat.cpp \
    ../../Libraries/ode-0.12/ode/src/matrix.cpp \
    ../../Libraries/ode-0.12/ode/src/memory.cpp \
    ../../Libraries/ode-0.12/ode/src/misc.cpp \
    ../../Libraries/ode-0.12/ode/src/nextafterf.c \
    ../../Libraries/ode-0.12/ode/src/obstack.cpp \
    ../../Libraries/ode-0.12/ode/src/ode.cpp \
    ../../Libraries/ode-0.12/ode/src/odeinit.cpp \
    ../../Libraries/ode-0.12/ode/src/odemath.cpp \
    ../../Libraries/ode-0.12/ode/src/odeou.cpp \
    ../../Libraries/ode-0.12/ode/src/odetls.cpp \
    ../../Libraries/ode-0.12/ode/src/plane.cpp \
    ../../Libraries/ode-0.12/ode/src/quickstep.cpp \
    ../../Libraries/ode-0.12/ode/src/ray.cpp \
    ../../Libraries/ode-0.12/ode/src/rotation.cpp \
    ../../Libraries/ode-0.12/ode/src/sphere.cpp \
    ../../Libraries/ode-0.12/ode/src/step.cpp \
    ../../Libraries/ode-0.12/ode/src/timer.cpp \
    ../../Libraries/ode-0.12/ode/src/util.cpp \
    ../../Libraries/ode-0.12/ode/src/joints/amotor.cpp \
    ../../Libraries/ode-0.12/ode/src/joints/ball.cpp \
    ../../Libraries/ode-0.12/ode/src/joints/contact.cpp \
    ../../Libraries/ode-0.12/ode/src/joints/fixed.cpp \
    ../../Libraries/ode-0.12/ode/src/joints/hinge.cpp \
    ../../Libraries/ode-0.12/ode/src/joints/hinge2.cpp \
    ../../Libraries/ode-0.12/ode/src/joints/joint.cpp \
    ../../Libraries/ode-0.12/ode/src/joints/lmotor.cpp \
    ../../Libraries/ode-0.12/ode/src/joints/null.cpp \
    ../../Libraries/ode-0.12/ode/src/joints/piston.cpp \
    ../../Libraries/ode-0.12/ode/src/joints/plane2d.cpp \
    ../../Libraries/ode-0.12/ode/src/joints/pr.cpp \
    ../../Libraries/ode-0.12/ode/src/joints/pu.cpp \
    ../../Libraries/ode-0.12/ode/src/joints/slider.cpp \
    ../../Libraries/ode-0.12/ode/src/joints/universal.cpp

*/
