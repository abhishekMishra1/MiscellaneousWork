#include <GL\glew.h>
#include <stdio.h>
#include <stdlib.h>

const char* VERTEX_SHADER_SRC = 
	"attribute vec4 a_Position;						\n"
	"attribute vec4 a_Color;						\n"
	"attribute vec2 a_TextureCoordinate;			\n"
	"varying vec4 v_Color;							\n"
	"varying vec2 v_TextureCoordinate;				\n"
	"uniform mat4 u_ModelMatrix;					\n"
	"uniform mat4 u_ProjectionMatrix;				\n"
	"uniform mat4 u_ViewMatrix;						\n"
	"void main() {									\n"
	"	gl_Position = u_ProjectionMatrix * u_ViewMatrix * u_ModelMatrix * a_Position;	\n"
	"	v_Color		= a_Color;						\n"
	"	v_TextureCoordinate = a_TextureCoordinate;	\n"
"}";

const char* FRAGMENT_SHADER_SRC = 
	"varying vec4 v_Color;							\n"
	"varying vec2 v_TextureCoordinate;				\n"
	"uniform sampler2D	activeTexture;				\n"
	"void main() {									\n"
	"	vec4 textureColor = texture2D(activeTexture, v_TextureCoordinate);	\n"
//	"vec4 color = vec4(1.0, , textureColor.g, textureColor.b, textureColor.a);\n"
	"	gl_FragColor = textureColor;// * v_Color;						\n"
	"	}";

int createShader(const char* src, int shaderType)
{
	int shaderID = glCreateShader(shaderType);
	
	//attach the src code to the shader object
	glShaderSource(shaderID, 1, &src, 0);

	//compile shader object
	glCompileShader(shaderID);

	//check if compilation is successful
	GLint success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if(success)
	{
		printf("Successfully compiled Shader\n");
	}
	else
	{
		printf("Failed to compile Shader\n");
		return -1;
	}

	return shaderID;
}

int createProgram()
{
	int vertexShader = createShader(VERTEX_SHADER_SRC, GL_VERTEX_SHADER);
	if(vertexShader < 0)
	{
		return -1;
	}

	int fragmentShader = createShader(FRAGMENT_SHADER_SRC, GL_FRAGMENT_SHADER);
	if(fragmentShader < 0)
	{
		return -1;
	}

	//create the program object(linker)
	int programObject = glCreateProgram();

	//attach the shader object to the program object
	glAttachShader(programObject, vertexShader);
	glAttachShader(programObject, fragmentShader);

	//link the program objec
	glLinkProgram(programObject);

	GLint success = 0;

	glGetProgramiv(programObject, GL_LINK_STATUS, &success);
	if(success)
	{
		printf("Linking successful\n");
	}
	else
	{
		GLint length = 0;
		glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &length);
		char* log = (char*)malloc(length);
		glGetProgramInfoLog(programObject, length, &length, log);
		printf("Linking failed\n%s", log);
		
		return -1;
	}

	return programObject;
}

