#version 460 core

void main()
{
	gl_FragDepth = gl_FragCoord.z;	//technically this main fucntion does not need this.
}
