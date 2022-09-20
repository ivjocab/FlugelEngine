#ifndef __PhysBody3D_H__
#define __PhysBody3D_H__

#include "p2List.h"
#include "Bullet/include/LinearMath/btQuaternion.h"

class btRigidBody;
class Module;
class vec3;

// =================================================
struct PhysBody3D
{
	friend class ModulePhysics3D;
public:
	PhysBody3D(btRigidBody* body);
	~PhysBody3D();

	void Push(float x, float y, float z);
	void GetTransform(float* matrix) const;
	void SetTransform(const float* matrix) const;
	void SetPos(float x, float y, float z);
	btQuaternion GetRotation() const;
	void SetRotation(btQuaternion& quat);
	void SetLinearVelocity(float x, float y, float z);
	void SetAngularVelocity(float x, float y, float z);
	vec3 GetLinearVelocity() const;

	const vec3 GetPos() const;

private:
	btRigidBody* body = nullptr;

public:
	p2List<Module*> collision_listeners;
	float rotation;
};

#endif // __PhysBody3D_H__