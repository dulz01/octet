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

    btRigidBody *bridge[11];

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
      mat.translate(-14, 0, 0);
      mesh_instance *left_ground = app_scene->add_shape(mat, new mesh_box(vec3(1, 1, 20), 1), red, false);
      bridge[0] = left_ground->get_node()->get_rigid_body();

      for (int i = 1; i != sizeof(bridge) - 1; ++i) {
        mat.loadIdentity();
        mat.translate(-14 + (i * 2), 0, 0);
        mesh_instance *m = app_scene->add_shape(mat, new mesh_box(vec3(0.8f, 0.1f, 10), 1), green, false);
        bridge[i] = m->get_node()->get_rigid_body();
      }

      //mat.loadIdentity();
      //mat.translate(-8, 0, 0);
      //mesh_instance *plank1 = app_scene->add_shape(mat, new mesh_box(vec3(0.8f, 0.1f, 10), 1), green, true);
      //btRigidBody *rb_plank1 = plank1->get_node()->get_rigid_body();

      //mat.loadIdentity();
      //mat.translate(-6, 0, 0);
      //mesh_instance *plank2 = app_scene->add_shape(mat, new mesh_box(vec3(0.8f, 0.1f, 10), 1), green, true);
      //btRigidBody *rb_plank2 = plank2->get_node()->get_rigid_body();

      //mat.loadIdentity();
      //mat.translate(-4, 0, 0);
      //mesh_instance *plank3 = app_scene->add_shape(mat, new mesh_box(vec3(0.8f, 0.1f, 10), 1), green, true);
      //btRigidBody *rb_plank3 = plank3->get_node()->get_rigid_body();

      //mat.loadIdentity();
      //mat.translate(-2, 0, 0);
      //mesh_instance *plank4 = app_scene->add_shape(mat, new mesh_box(vec3(0.8f, 0.1f, 10), 1), green, true);
      //btRigidBody *rb_plank4 = plank4->get_node()->get_rigid_body();

      //mat.loadIdentity();
      //mat.translate(0, 0, 0);
      //mesh_instance *plank5 = app_scene->add_shape(mat, new mesh_box(vec3(0.8f, 0.1f, 10), 1), green, true);
      //btRigidBody *rb_plank5 = plank5->get_node()->get_rigid_body();

      //mat.loadIdentity();
      //mat.translate(2, 0, 0);
      //mesh_instance *plank6 = app_scene->add_shape(mat, new mesh_box(vec3(0.8f, 0.1f, 10), 1), green, true);
      //btRigidBody *rb_plank6 = plank6->get_node()->get_rigid_body();

      //mat.loadIdentity();
      //mat.translate(4, 0, 0);
      //mesh_instance *plank7 = app_scene->add_shape(mat, new mesh_box(vec3(0.8f, 0.1f, 10), 1), green, true);
      //btRigidBody *rb_plank7 = plank7->get_node()->get_rigid_body();

      //mat.loadIdentity();
      //mat.translate(6, 0, 0);
      //mesh_instance *plank8 = app_scene->add_shape(mat, new mesh_box(vec3(0.8f, 0.1f, 10), 1), green, true);
      //btRigidBody *rb_plank8 = plank8->get_node()->get_rigid_body();

      //mat.loadIdentity();
      //mat.translate(8, 0, 0);
      //mesh_instance *plank9 = app_scene->add_shape(mat, new mesh_box(vec3(0.8f, 0.1f, 10), 1), green, true);
      //btRigidBody *rb_plank9 = plank9->get_node()->get_rigid_body();

      mat.loadIdentity();
      mat.translate(14, 0, 0);
      mesh_instance *right_ground = app_scene->add_shape(mat, new mesh_box(vec3(1, 1, 20), 1), red, false);
      bridge[10] = right_ground->get_node()->get_rigid_body();
      
      //btTransform tran1 = btTransform::getIdentity();
      //tran1.setOrigin(btVector3(0.8f, 0, 48.0f));

      //btTransform tran2 = btTransform::getIdentity();
      //tran2.setOrigin(btVector3(-0.8f, 0, 48.0f));

      //app_scene->applySpring(rb_left_ground, rb_plank1, tran1, tran2);
      //app_scene->applySpring(rb_plank1, rb_plank2, tran1, tran2);
      //app_scene->applySpring(rb_plank2, rb_plank3, tran1, tran2);
      //app_scene->applySpring(rb_plank3, rb_plank4, tran1, tran2);
      //app_scene->applySpring(rb_plank4, rb_plank5, tran1, tran2);
      //app_scene->applySpring(rb_plank5, rb_plank6, tran1, tran2);
      //app_scene->applySpring(rb_plank6, rb_plank7, tran1, tran2);
      //app_scene->applySpring(rb_plank7, rb_plank8, tran1, tran2);
      //app_scene->applySpring(rb_plank8, rb_plank9, tran1, tran2);
      //app_scene->applySpring(rb_plank9, rb_right_ground, tran1, tran2);

      //tran1 = btTransform::getIdentity();
      //tran1.setOrigin(btVector3(0.8f, 0, -48.0f));

      //tran2 = btTransform::getIdentity();
      //tran2.setOrigin(btVector3(-0.8f, 0, -48.0f));

      //app_scene->applySpring(rb_left_ground, rb_plank1, tran1, tran2);
      //app_scene->applySpring(rb_plank1, rb_plank2, tran1, tran2);
      //app_scene->applySpring(rb_plank2, rb_plank3, tran1, tran2);
      //app_scene->applySpring(rb_plank3, rb_plank4, tran1, tran2);
      //app_scene->applySpring(rb_plank4, rb_plank5, tran1, tran2);
      //app_scene->applySpring(rb_plank5, rb_plank6, tran1, tran2);
      //app_scene->applySpring(rb_plank6, rb_plank7, tran1, tran2);
      //app_scene->applySpring(rb_plank7, rb_plank8, tran1, tran2);
      //app_scene->applySpring(rb_plank8, rb_plank9, tran1, tran2);
      //app_scene->applySpring(rb_plank9, rb_right_ground, tran1, tran2);
      //-----------------------------------------------------------------------

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
      //btVector3 pivotInA = btVector3(0, 0, 0);
      //btVector3 pivotInB = btVector3(-10, 0, 0);

      //app_scene->applyPoint2PointConstraint(rigid_body1, rigid_body2, pivotInA, pivotInB);
      
      // for the spring constraint.
      //btTransform tran1 = btTransform::getIdentity();
      //tran1.setOrigin(btVector3(0, 0, 0));

      //btTransform tran2 = btTransform::getIdentity();
      //tran2.setOrigin(btVector3(-10, 0, 0));

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
