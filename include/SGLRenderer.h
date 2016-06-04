#ifndef SIMPLEGL_RENDERER
#define SIMPLEGL_RENDERER 

#include <GL/glew.h>
#include <SGLShader.h>
#include <SGLShaderProgram.h>
#include <SGLRenderable.h>

#include <string>

class SGLRenderer
{
public:
	SGLRenderer();
	SGLRenderer(std::string vertShaderPath, std::string fragShaderPath);
	~SGLRenderer();

	void draw(SGLRenderable &target);
	void attachShaders(std::string vertShaderPath, std::string fragShaderPath);
	void attachShaders(SGLShader vertShader, SGLShader fragShader);
		
	SGLShaderProgram shaderProgram;
	SGLShaderProgram getShaderProgram();
private:
	/* data */
	SGLShader vertShader;
	SGLShader fragShader;
};

#endif /* ifndef SIMPLEGL_RENDERER */
