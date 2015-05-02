#pragma once

#include "gVertexBuffer.h"

class GeometryHelper
{
public:
	GeometryHelper(gVertexBuffer * const &vertexBufferManager);
	virtual void initialize() = 0;
	virtual int getTheNumberOfVerticies() = 0;

protected:
	gVertexBuffer * const &vertexBufferManager;
};


class QuadGeometryHelper : public GeometryHelper
{
public:
	QuadGeometryHelper(gVertexBuffer * const &vertexBufferManager);
	void initialize();
	int getTheNumberOfVerticies();
};


class CuboidGeometryHelper : public GeometryHelper
{
public:
	CuboidGeometryHelper(gVertexBuffer * const &vertexBufferManager);
	void initialize();
	int getTheNumberOfVerticies();
};


class SphereGeometryHelper : public GeometryHelper
{
public:
	SphereGeometryHelper(gVertexBuffer * const &vertexBufferManager);
	void initialize();
	int getTheNumberOfVerticies();
};


class CylinderGeometryHelper : public GeometryHelper
{
public:
	CylinderGeometryHelper(gVertexBuffer * const &vertexBufferManager);
	void initialize();
	int getTheNumberOfVerticiesForShield();
	int getTheNumberOfVerticiesForBottom();
	int getTheNumberOfVerticiesForTop();
	int getTheNumberOfVerticies();
private:
	void initializeShield();
	void initializeBottom();
	void initializeTop();
};


class DiamondGeometryHelper : public GeometryHelper
{
public:
	DiamondGeometryHelper(gVertexBuffer * const &vertexBufferManager);
	void initialize();
	int getTheNumberOfVerticiesForBottomPyramid();
	int getTheNumberOfVerticiesForTopPyramid();
	int getTheNumberOfVerticies();
private:
	void initializeBottomPyramid();
	void initializeTopPyramid();
};