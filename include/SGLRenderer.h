#ifndef SIMPLEGL_RENDERER
#define SIMPLEGL_RENDERER 

#include <GL/Glew.h>
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

	void draw(SGLRenderable target);
	void attachShaders(std::string vertShaderPath, std::string fragShaderPath);
	void attachShaders(SGLShader vertShader, SGLShader fragShader);
		
	SGLShaderProgram getShaderProgram();
private:
	/* data */
	SGLShaderProgram shaderProgram;
	SGLShader vertShader;
	SGLShader fragShader;
};

#endif /* ifndef SIMPLEGL_RENDERER */
