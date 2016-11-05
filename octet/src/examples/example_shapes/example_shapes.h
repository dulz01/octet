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
            
      // building the bridge
      mat.loadIdentity();
      mat.translate(-14, 0, 0);
      mesh_instance *left_ground = app_scene->add_shape(mat, new mesh_box(vec3(1, 1, 20), 1), red, false);
      bridge[0] = left_ground->get_node()->get_rigid_body();

      for (int i = 1; i != numObjects - 1; ++i) {
        mat.loadIdentity();
        mat.translate(-12 + (i * 2), 0, 0);
        mesh_instance *m = app_scene->add_shape(mat, new mesh_box(vec3(0.8f, 0.1f, 10), 1), green, true);
        bridge[i] = m->get_node()->get_rigid_body();
      }

      mat.loadIdentity();
      mat.translate(14, 0, 0);
      mesh_instance *right_ground = app_scene->add_shape(mat, new mesh_box(vec3(1, 1, 20), 1), red, false);
      bridge[10] = right_ground->get_node()->get_rigid_body();
      
      // setting up the constraints
      btTransform tran1 = btTransform::getIdentity();
      tran1.setOrigin(btVector3(0.8f, 0, 18.0f));

      btTransform tran2 = btTransform::getIdentity();
      tran2.setOrigin(btVector3(-0.8f, 0, 18.0f));

      for (int i = 0; i != numObjects - 1; ++i) {
        app_scene->applySpring(bridge[i], bridge[i + 1], tran1, tran2);
      }

      tran1 = btTransform::getIdentity();
      tran1.setOrigin(btVector3(0.8f, 0, -18.0f));

      tran2 = btTransform::getIdentity();
      tran2.setOrigin(btVector3(-0.8f, 0, -18.0f));

      for (int i = 0; i != numObjects - 1; ++i) {
        app_scene->applySpring(bridge[i], bridge[i + 1], tran1, tran2);
      }      
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
