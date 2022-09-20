#include "PhysBody3D.h"
#include "glmath.h"
#include "Bullet/include/btBulletDynamicsCommon.h"
#include "Bullet/include/LinearMath/btQuaternion.h"

// =================================================
PhysBody3D::PhysBody3D(btRigidBody* body) : body(body)
{}

// ---------------------------------------------------------
PhysBody3D::~PhysBody3D()
{
	delete body;
}

// ---------------------------------------------------------
void PhysBody3D::Push(float x, float y, float z)
{
	body->applyCentralImpulse(btVector3(x, y, z));
}

// ---------------------------------------------------------
void PhysBody3D::GetTransform(float* matrix) const
{
	if(body != NULL && matrix != NULL)
	{
		body->getWorldTransform().getOpenGLMatrix(matrix);
	}
}

const vec3 PhysBody3D::GetPos() const
{
	btTransform t = body->getWorldTransform();
	btVector3 v = t.getOrigin();
	vec3 ret; ret.Set(v.getX(), v.getY(), v.getZ());
	return ret;
}

// ---------------------------------------------------------
void PhysBody3D::SetTransform(const float* matrix) const
{
	if(body != NULL && matrix != NULL)
	{
		btTransform t;
		t.setFromOpenGLMatrix(matrix);
		body->setWorldTransform(t);
	}
}

// ---------------------------------------------------------
void PhysBody3D::SetPos(float x, float y, float z)
{
	btTransform t = body->getWorldTransform();
	t.setOrigin(btVector3(x, y, z));
	body->setWorldTransform(t);
}

btQuaternion PhysBody3D::GetRotation() const
{
	return body->getWorldTransform().getRotation();
}

void PhysBody3D::SetRotation(btQuaternion& quat)
{
	btTransform t = body->getWorldTransform();
	t.setRotation(quat);
	body->setWorldTransform(t);
}

void PhysBody3D::SetLinearVelocity(float x, float y, float z)
{
	btVector3 v(x, y, z);
	body->setLinearVelocity(v);
}

vec3 PhysBody3D::GetLinearVelocity() const
{
	const btVector3 v = body->getLinearVelocity();
	vec3 ret = (v.getX(), v.getY(), v.getZ());
	return ret;
}

void PhysBody3D::SetAngularVelocity(float x, float y, float z)
{
	btVector3 v(x, y, z);
	body->setAngularVelocity(v);
}
