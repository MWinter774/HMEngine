#version 330

layout(location = 0) in vec3 inPosition;

out vec2 textureCoordinates;

// Values that stay constant for the whole mesh.
uniform vec3 CameraRight_worldspace;
uniform vec3 CameraUp_worldspace;
uniform mat4 VP; // Model-View-Projection matrix, but without the Model (the position is in BillboardPos; the orientation depends on the camera)
uniform vec3 BillboardPos; // Position of the center of the billboard
uniform vec2 BillboardSize; // Size of the billboard, in world units (probably meters)

void main()
{
	vec3 particleCenter_wordspace = BillboardPos;
	
	vec3 vertexPosition_worldspace = 
		particleCenter_wordspace
		+ CameraRight_worldspace * inPosition.x * BillboardSize.x
		+ CameraUp_worldspace * inPosition.y * BillboardSize.y;


	gl_Position = VP * vec4(vertexPosition_worldspace, 1.0f);

	//textureCoordinates = inPosition.xy + vec2(0.5, 0.5);
	textureCoordinates = vec2((inPosition.x + 1.0) / 2.0, 1 - (inPosition.y + 1.0) / 2.0);
}