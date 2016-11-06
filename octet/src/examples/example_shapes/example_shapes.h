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

    int numObjects = 11;
    btRigidBody *bridge[11];
    mat4t mat;

    material *red;
    material *green;
    material *blue;
    material *yellow;
    material *pink;

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
            
      red = new material(vec4(1, 0, 0, 1));
      green = new material(vec4(0, 1, 0, 1));
      blue = new material(vec4(0, 0, 1, 1));
      yellow = new material(vec4(1, 1, 0, 1));
      pink = new material(vec4(1, 0, 1, 1));

      // building the bridge
      // left ground
      mat.loadIdentity();
      mat.translate(-14, 0, 0);
      mesh_instance *left_ground = app_scene->add_shape(mat, new mesh_box(vec3(1, 1, 20), 1), red, false);
      bridge[0] = left_ground->get_node()->get_rigid_body();

      // planks
      for (int i = 1; i < numObjects - 1; ++i) {
        mat.loadIdentity();
        mat.translate(-12 + (i * 2), 0, 0);
        mesh_instance *m = app_scene->add_shape(mat, new mesh_box(vec3(0.8f, 0.1f, 10), 1), green, true);
        bridge[i] = m->get_node()->get_rigid_body();
      }

      // right ground
      mat.loadIdentity();
      mat.translate(14, 0, 0);
      mesh_instance *right_ground = app_scene->add_shape(mat, new mesh_box(vec3(1, 1, 20), 1), red, false);
      bridge[numObjects - 1] = right_ground->get_node()->get_rigid_body();
      
      // setting up the constraints
      btTransform tran1 = btTransform::getIdentity();
      tran1.setOrigin(btVector3(0.8f, 0, 18.0f));

      btTransform tran2 = btTransform::getIdentity();
      tran2.setOrigin(btVector3(-0.8f, 0, 18.0f));

      for (int i = 0; i < numObjects - 1; ++i) {
        app_scene->applySpring(bridge[i], bridge[i + 1], tran1, tran2);
      }

      tran1 = btTransform::getIdentity();
      tran1.setOrigin(btVector3(0.8f, 0, -18.0f));

      tran2 = btTransform::getIdentity();
      tran2.setOrigin(btVector3(-0.8f, 0, -18.0f));

      for (int i = 0; i < numObjects - 1; ++i) {
        app_scene->applySpring(bridge[i], bridge[i + 1], tran1, tran2);
      }

      mat.loadIdentity();
      mat.translate(0, -10, 0);
      app_scene->add_shape(mat, new mesh_box(vec3(28, 1, 20), 1), blue, false);
    }

    // spawns cubes to collide with the bridge
    void spawnObjects() {
      if (is_key_down(key_q)) {
        mat.loadIdentity();
        mat.translate(-9, 5, 3);
        app_scene->add_shape(mat, new mesh_box(vec3(0.1f, 0.1f, 0.1f), 1), red, true);
      }

      if (is_key_down(key_w)) {
        mat.loadIdentity();
        mat.translate(-4, 5, 3);
        app_scene->add_shape(mat, new mesh_box(vec3(0.1f, 0.1f, 0.1f), 1), yellow, true);
      }

      if (is_key_down(key_e)) {
        mat.loadIdentity();
        mat.translate(0, 5, 3);
        app_scene->add_shape(mat, new mesh_box(vec3(0.1f, 0.1f, 0.1f), 1), pink, true);
      }

      if (is_key_down(key_r)) {
        mat.loadIdentity();
        mat.translate(6, 5, 3);
        app_scene->add_shape(mat, new mesh_box(vec3(0.1f, 0.1f, 0.1f), 1), blue, true);
      }

      if (is_key_going_down(key_a)) {
        mat.loadIdentity();
        mat.translate(-9, 5, -3);
        app_scene->add_shape(mat, new mesh_cylinder(vec3(0.1f, 0.1f, 0.1f), 1), blue, true);
      }

      if (is_key_going_down(key_s)) {
        mat.loadIdentity();
        mat.translate(-4, 5, -3);
        app_scene->add_shape(mat, new mesh_sphere(vec3(0.1f, 0.1f, 0.1f), 1), pink, true);
      }

      if (is_key_going_down(key_d)) {
        mat.loadIdentity();
        mat.translate(0, 5, -3);
        app_scene->add_shape(mat, new mesh_box(vec3(1.0f, 1.0f, 1.0f), 1), yellow, true);
      }
    }

    /// this is called to draw the world
    void draw_world(int x, int y, int w, int h) {
      spawnObjects();

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
