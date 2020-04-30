1: Application Creation and Game Loop:
Create Application like this
	Application app;
	ApplicationConfig config = {};
	app.Init(config);
	app.Run();

Application::Init and Application::Run functions return true and false on success and failure respectively check for the returns and
exit with a log and failure status
	if(!app.Init(config))
		'failed to init app with config %', config;
	if(!app.Run())
		'failed to run app';

Jin uses Layers as wrappers over loops
Create a Layer by inheriting from base Layer class
the Start, Update and End function needs to be overriden with your own implementation
	virtual void Start() override
	virtual void Update() override
	virtual void End() override
these functions should be self explaning Start and End are executed once and Update is looped untill the applicatin is open
a sample Layer would look like this
	class MainLayer: public Layer
	{
	public:
		MainLayer() : Layer("main_layer") {}
		virtual void Start() override {}
		virtual void Update() override {}
		virtual void End() override {}
	};

add the layer to the app before running the app
	app.AddLayer(new MainLayer());
	app.Run();
the layer is then released internally when app is closed so this is not a memory leak

2: Renderer and Cameras
Jin has a good implementation of a 2d batch renderer that can draw textured quads.
To Draw a single quad you need to start a batch, draw, end and flush the batch
	BatchRenderer2D::Begin();
	BatchRenderer2D::DrawQuad(position, size, color);
	BatchRenderer2D::End();
	BatchRenderer2D::Flush();
the app takes care of the buffer swapping internally and vsync can be configured through ApplicationConfiguration struct
the renderer needs to initialized in the Layers Start function this may change in future versions of Jin
	virtual void Start() override
	{
		BatchRenderer2DConfig config = {};
		BatchRenderer2D::Init(config);
	}
