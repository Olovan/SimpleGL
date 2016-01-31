#include <GL/glew.h>
#include <Vertex.h>

class SGLBatchBuffer
{
	public:
		SGLBatchBuffer();
		SGLBatchBuffer(GLuint size);

		int size;
		GLuint currentOffset = 0;
		GLuint bufferID;

		void bind();
		void unbind();
		void createBuffer();
		void createBuffer(GLuint size);
		void destroyBuffer();
		void setBufferData(GLuint size);
		void subBufferData(GLuint offset, GLuint sizeOfDataBytes, void* data);
		bool insertData(GLuint sizeOfDataBytes, void* data);
		void draw();
};
