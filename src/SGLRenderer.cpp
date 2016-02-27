#include <SGLRenderer.h>

//Constructors and Destructors
SGLRenderer::SGLRenderer()
{

}

SGLRenderer::SGLRenderer(std::string vertPath, std::string fragPath) 
{
	attachShaders(vertPath, fragPath);	
}

SGLRenderer::~SGLRenderer()
{

}

//Member Functions

void SGLRenderer::attachShaders(std::string vertShaderPath, std::string fragShaderPath) 
{
	vertShader.compileFromFile(vertShaderPath, GL_VERTEX_SHADER);  
	fragShader.compileFromFile(fragShaderPath, GL_FRAGMENT_SHADER);

	shaderProgram.attachShader(vertShader);	
	shaderProgram.attachShader(fragShader);
	shaderProgram.linkProgram();
	shaderProgram.validateProgram();
}

void SGLRenderer::attachShaders(SGLShader vertShader, SGLShader fragShader) 
{
	shaderProgram.attachShader(vertShader);	
	shaderProgram.attachShader(fragShader);
}

void SGLRenderer::draw(SGLRenderable target) 
{
	shaderProgram.useProgram();
	target.draw();	
}

//Getters and Setters
SGLShaderProgram SGLRenderer::getShaderProgram() 
{
	return shaderProgram;	
}

