class globalConstants {
	public:
		//Screen dimension constants
		globalConstants();
		const int SCREEN_WIDTH;
		const int SCREEN_HEIGHT;
		const int X;
		const int Y;
		const int BRICK_HEIGHT;
		const int BRICK_WIDTH;
		const int LEP_HEIGHT;
		const int LEP_WIDTH;
};

globalConstants::globalConstants()
{
		const int SCREEN_WIDTH = 500;
		const int SCREEN_HEIGHT = 480;
		const int X = 0;
		const int Y = 1;
		const int BRICK_HEIGHT = 32;
		const int BRICK_WIDTH = 32;
		const int LEP_HEIGHT = 44;
		const int LEP_WIDTH = 25;
}