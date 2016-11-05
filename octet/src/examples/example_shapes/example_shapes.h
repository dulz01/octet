////////////////////////////////////////////////////////////////////////////////
//
// (C) Andy Thomason 2012-2014
//
// Modular Framework for OpenGLES2 rendering on multiple platforms.
//
namespace octet {
  /// Scene containing a box with octet.
  class example_shapes : public app {
    // scene for drawing box
    ref<visual_scene> app_scene;

  public:
    example_shapes(int argc, char **argv) : app(argc, argv) {
    }

    ~example_shapes() {
    }

    /// this is called once OpenGL is initialized
    void app_init() {
      app_scene = new visual_scene();
      app_scene->create_default_camera_and_lights();
      app_scene->get_camera_instance(0)->get_node()->translate(vec3(0, 4, 0));

      material *red = new material(vec4(1, 0, 0, 1));
      material *green = new material(vec4(0, 1, 0, 1));
      material *blue = new material(vec4(0, 0, 1, 1));
      material *yellow = new material(vec4(1, 1, 0, 1));

      mat4t mat;

      //-----------------------------------------------------------------------
      // bridge
      //-----------------------------------------------------------------------
      mat.loadIdentity();
      mat.translate(-10, 0, 0);
      mesh_instance *left_ground = app_scene->add_shape(mat, new mesh_box(vec3(1, 1, 20), 1), red, false);

      mat.loadIdentity();
      mat.translate(-8, 0, 0);
      mesh_instance *plank1 = app_scene->add_shape(mat, new mesh_box(vec3(0.1f, 0.1f, 20), 1), green, false);

      mat.loadIdentity();
      mat.translate(-6, 0, 0);
      mesh_instance *plank2 = app_scene->add_shape(mat, new mesh_box(vec3(0.1f, 0.1f, 20), 1), green, false);

      mat.loadIdentity();
      mat.translate(-4, 0, 0);
      mesh_instance *plank3 = app_scene->add_shape(mat, new mesh_box(vec3(0.1f, 0.1f, 20), 1), green, false);

      mat.loadIdentity();
      mat.translate(-2, 0, 0);
      mesh_instance *plank4 = app_scene->add_shape(mat, new mesh_box(vec3(0.1f, 0.1f, 20), 1), green, false);

      mat.loadIdentity();
      mat.translate(0, 0, 0);
      mesh_instance *plank5 = app_scene->add_shape(mat, new mesh_box(vec3(0.1f, 0.1f, 20), 1), green, false);

      mat.loadIdentity();
      mat.translate(2, 0, 0);
      mesh_instance *plank6 = app_scene->add_shape(mat, new mesh_box(vec3(0.1f, 0.1f, 20), 1), green, false);

      mat.loadIdentity();
      mat.translate(4, 0, 0);
      mesh_instance *plank7 = app_scene->add_shape(mat, new mesh_box(vec3(0.1f, 0.1f, 20), 1), green, false);

      mat.loadIdentity();
      mat.translate(6, 0, 0);
      mesh_instance *plank8 = app_scene->add_shape(mat, new mesh_box(vec3(0.1f, 0.1f, 20), 1), green, false);

      mat.loadIdentity();
      mat.translate(8, 0, 0);
      mesh_instance *plank9 = app_scene->add_shape(mat, new mesh_box(vec3(0.1f, 0.1f, 20), 1), green, false);

      mat.loadIdentity();
      mat.translate(10, 0, 0);
      mesh_instance *right_ground = app_scene->add_shape(mat, new mesh_box(vec3(1, 1, 20), 1), red, false);
      //-----------------------------------------------------------------------
      // Test spheres
      //-----------------------------------------------------------------------
      //mat.loadIdentity();
      //mat.translate(-10, 6, 0);
      //mesh_instance * pin = app_scene->add_shape(mat, new mesh_sphere(vec3(2, 2, 2), 2), red, false);
      //btRigidBody * rigid_body1 = pin->get_node()->get_rigid_body();

      //mat.loadIdentity();
      //mat.translate(10, 3, 0);
      //mesh_instance * ball = app_scene->add_shape(mat, new mesh_sphere(vec3(2, 2, 2), 2), green, true);
      //btRigidBody * rigid_body2 = ball->get_node()->get_rigid_body();
      //-----------------------------------------------------------------------
      
      // for the point2point constraint
      btVector3 pivotInA = btVector3(0, 0, 0);
      btVector3 pivotInB = btVector3(-10, 0, 0);

      //app_scene->applyPoint2PointConstraint(rigid_body1, rigid_body2, pivotInA, pivotInB);
      
      // for the spring constraint.
      btTransform tran1 = btTransform::getIdentity();
      tran1.setOrigin(btVector3(0, 0, 0));

      btTransform tran2 = btTransform::getIdentity();
      tran2.setOrigin(btVector3(-10, 0, 0));

      //app_scene->applySpring(rigid_body1, rigid_body2, tran1, tran2);

      // for the hinge constraint
      //app_scene->applyHinge(rigid_body2, btVector3(0, 10, 0), btVector3(0, 1.0f, 0));
      
    }

    /// this is called to draw the world
    void draw_world(int x, int y, int w, int h) {
      int vx = 0, vy = 0;
      get_viewport_size(vx, vy);
      app_scene->begin_render(vx, vy);

      // update matrices. assume 30 fps.
      app_scene->update(1.0f / 30);

      // draw the scene
      app_scene->render((float)vx / vy);
    }
  };
}
