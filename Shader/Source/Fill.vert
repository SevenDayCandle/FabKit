#version 450

layout (location = 0) in vec3 Position;

layout (set = 1, binding = 0) uniform UniformBlock
{
	mat4x4 MatrixTransform;
};

void main()
{
	gl_Position = MatrixTransform * vec4(Position, 1);
}