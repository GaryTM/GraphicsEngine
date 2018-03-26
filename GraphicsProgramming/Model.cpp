#include <glm\gtc\type_ptr.hpp>

#include "Model.hpp"
#include "Errors.hpp"

/*These privates variables are being initialised using an inistialisation list
which only works for constructors, but is faster than adding
_drawCount = NULL; etc. to the body of the constructor. REMEMBER THIS!*/
Model::Model() :
	_drawCount(NULL)
{
}

Model::~Model()
{
}

void Model::init(Vertex3D* vertices, unsigned int verticeCount, unsigned int* indices, unsigned int indiceCount)
{
	IndexedModel model;

	for (unsigned int i = 0; i < verticeCount; i++)
	{
		model.positions.push_back(*vertices[i].GetPosition());
		model.texCoords.push_back(*vertices[i].GetTextureCoords());
		model.normals.push_back(*vertices[i].GetNormal());
	}

	for (unsigned int i = 0; i < indiceCount; i++)
		model.indices.push_back(indices[i]);

	initModel(model);
}

void Model::loadModel(const string& filename)
{
	IndexedModel model = OBJModel(filename).ToIndexedModel();
	initModel(model);
	Sphere _modelCollisionSphere();
}
void Model::initModel(const IndexedModel& model)
{
	_drawCount = model.indices.size();

	//******************** ATTRIBUTE ONE: POSITION ********************
	//Generate the vertex array based on number and storing it in the VAO
	glGenVertexArrays(1, &_vertexArrayObject);
	//Binding the model VAO
	glBindVertexArray(_vertexArrayObject);
	//Generate the buffers using the array of buffer data
	glGenBuffers(BUFFER_COUNT, _vertexArrayBuffers);
	//Letting OpenGL know what type of data the buffer contains and passing it the data!
	glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayBuffers[VERTEX_BUFFER_POSITION]);
	//Chucking the data to the GPU :D
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);
	//Enable the vertex attribute array
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//******************** ATTRIBUTE TWO: TEXTURE COORDINATES **********
	glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayBuffers[VERTEX_BUFFER_TEXTURECOORDINATE]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//******************** ATTRIBUTE THREE: NORMALS ********************
	glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayBuffers[VERTEX_BUFFER_NORMAL]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.normals[0]) * model.normals.size(), &model.normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//******************** ATTRIBUTE FOUR: INDICES ********************
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vertexArrayBuffers[VERTEX_BUFFER_INDEX]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);
	//Unbind the VAO!
	glBindVertexArray(0);
}

void Model::updateCollisionSphere(vec3 position, float radius)
{
	_collisionSphere.SetPosition(position);
	_collisionSphere.SetRadius(radius);
}

void Model::draw()
{
	glBindVertexArray(_vertexArrayObject);

	glDrawElements(GL_TRIANGLES, _drawCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void Model::draw(const Camera& mainCamera, Shader* shader, Texture* texture)
{
	shader->bindShader();

	GLint transformLocation = shader->getUniformLocation("transform");
	mat4 mvp = (mainCamera.GetViewProjection() * transform.GetModel());
	/*glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);*/
	glUniformMatrix4fv(transformLocation, 1, GLU_FALSE, value_ptr(mvp));
	texture->bindTexture(0);
	draw();

	shader->unbindShader();
}
