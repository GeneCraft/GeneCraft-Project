#-------------------------------------------------
#
# Project created by QtCreator 2011-02-21T13:05:11
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = GeneLab

TEMPLATE = app

INCLUDEPATH += Bullet

SOURCES += \
    Bullet/BulletCollision/BroadphaseCollision/btBroadphaseProxy.cpp \
    Bullet/BulletCollision/BroadphaseCollision/btDispatcher.cpp \
    Bullet/BulletCollision/NarrowPhaseCollision/btConvexCast.cpp \
    Bullet/BulletCollision/CollisionDispatch/btEmptyCollisionAlgorithm.cpp \
    Bullet/BulletCollision/BroadphaseCollision/btCollisionAlgorithm.cpp \
    Bullet/BulletCollision/NarrowPhaseCollision/btGjkConvexCast.cpp \
    Bullet/BulletDynamics/ConstraintSolver/btSolve2LinearConstraint.cpp \
    Bullet/BulletCollision/BroadphaseCollision/btAxisSweep3.cpp \
    Bullet/BulletCollision/Gimpact/gim_memory.cpp \
    Bullet/BulletCollision/Gimpact/gim_contact.cpp \
    Bullet/BulletCollision/Gimpact/gim_box_set.cpp \
    Bullet/BulletDynamics/Vehicle/btWheelInfo.cpp \
    Bullet/BulletCollision/CollisionDispatch/btSphereSphereCollisionAlgorithm.cpp \
    Bullet/BulletCollision/CollisionDispatch/btSphereBoxCollisionAlgorithm.cpp \
    Bullet/BulletCollision/BroadphaseCollision/btMultiSapBroadphase.cpp \
    Bullet/LinearMath/btGeometryUtil.cpp \
    Bullet/BulletCollision/Gimpact/btContactProcessing.cpp \
    Bullet/BulletCollision/CollisionDispatch/btActivatingCollisionAlgorithm.cpp \
    Bullet/BulletCollision/CollisionDispatch/btGhostObject.cpp \
    Bullet/BulletCollision/NarrowPhaseCollision/btRaycastCallback.cpp \
    Bullet/BulletCollision/CollisionShapes/btUniformScalingShape.cpp \
    Bullet/BulletCollision/CollisionShapes/btTriangleMesh.cpp \
    Bullet/BulletCollision/CollisionShapes/btTriangleIndexVertexMaterialArray.cpp \
    Bullet/BulletCollision/CollisionShapes/btTriangleIndexVertexArray.cpp \
    Bullet/BulletCollision/CollisionShapes/btTriangleCallback.cpp \
    Bullet/BulletCollision/CollisionShapes/btTriangleBuffer.cpp \
    Bullet/BulletCollision/CollisionShapes/btSphereShape.cpp \
    Bullet/BulletCollision/CollisionShapes/btScaledBvhTriangleMeshShape.cpp \
    Bullet/BulletCollision/CollisionShapes/btMultimaterialTriangleMeshShape.cpp \
    Bullet/BulletCollision/CollisionShapes/btMinkowskiSumShape.cpp \
    Bullet/BulletCollision/CollisionShapes/btHeightfieldTerrainShape.cpp \
    Bullet/BulletCollision/CollisionShapes/btEmptyShape.cpp \
    Bullet/BulletCollision/CollisionShapes/btConeShape.cpp \
    Bullet/BulletCollision/CollisionShapes/btConcaveShape.cpp \
    Bullet/BulletCollision/CollisionShapes/btBoxShape.cpp \
    Bullet/BulletCollision/CollisionShapes/btCylinderShape.cpp \
    Bullet/BulletCollision/CollisionDispatch/SphereTriangleDetector.cpp \
    Bullet/BulletCollision/CollisionShapes/btTetrahedronShape.cpp \
    Bullet/BulletCollision/CollisionShapes/btStaticPlaneShape.cpp \
    Bullet/BulletCollision/CollisionDispatch/btSphereTriangleCollisionAlgorithm.cpp \
    Bullet/BulletCollision/CollisionShapes/btOptimizedBvh.cpp \
    Bullet/BulletCollision/CollisionShapes/btConvexTriangleMeshShape.cpp \
    Bullet/BulletCollision/CollisionShapes/btConvexPointCloudShape.cpp \
    Bullet/BulletCollision/CollisionShapes/btCapsuleShape.cpp \
    Bullet/BulletCollision/CollisionDispatch/btBoxBoxCollisionAlgorithm.cpp \
    Bullet/BulletDynamics/Dynamics/btSimpleDynamicsWorld.cpp \
    Bullet/BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.cpp \
    Bullet/BulletCollision/NarrowPhaseCollision/btPersistentManifold.cpp \
    Bullet/BulletCollision/CollisionShapes/btConvexInternalShape.cpp \
    Bullet/BulletCollision/NarrowPhaseCollision/btContinuousConvexCollision.cpp \
    Bullet/BulletCollision/CollisionShapes/btPolyhedralConvexShape.cpp \
    Bullet/BulletCollision/CollisionDispatch/btManifoldResult.cpp \
    Bullet/BulletCollision/NarrowPhaseCollision/btGjkEpaPenetrationDepthSolver.cpp \
    Bullet/BulletCollision/NarrowPhaseCollision/btGjkEpa2.cpp \
    Bullet/BulletCollision/CollisionShapes/btConvexShape.cpp \
    Bullet/BulletDynamics/Dynamics/btContinuousDynamicsWorld.cpp \
    Bullet/BulletCollision/CollisionDispatch/btConvexPlaneCollisionAlgorithm.cpp \
    Bullet/BulletCollision/NarrowPhaseCollision/btGjkPairDetector.cpp \
    Bullet/BulletCollision/CollisionDispatch/btCollisionDispatcher.cpp \
    Bullet/BulletDynamics/Dynamics/Bullet-C-API.cpp \
    Bullet/BulletCollision/CollisionDispatch/btConvexConcaveCollisionAlgorithm.cpp \
    Bullet/BulletCollision/Gimpact/btGImpactShape.cpp \
    Bullet/LinearMath/btConvexHull.cpp \
    Bullet/BulletCollision/NarrowPhaseCollision/btMinkowskiPenetrationDepthSolver.cpp \
    Bullet/BulletCollision/CollisionShapes/btShapeHull.cpp \
    Bullet/BulletCollision/BroadphaseCollision/btSimpleBroadphase.cpp \
    Bullet/BulletCollision/BroadphaseCollision/btDbvtBroadphase.cpp \
    Bullet/BulletDynamics/ConstraintSolver/btSliderConstraint.cpp \
    Bullet/BulletCollision/BroadphaseCollision/btOverlappingPairCache.cpp \
    Bullet/BulletDynamics/ConstraintSolver/btContactConstraint.cpp \
    Bullet/BulletDynamics/ConstraintSolver/btConeTwistConstraint.cpp \
    Bullet/BulletCollision/CollisionShapes/btTriangleMeshShape.cpp \
    Bullet/BulletCollision/NarrowPhaseCollision/btVoronoiSimplexSolver.cpp \
    Bullet/BulletCollision/BroadphaseCollision/btQuantizedBvh.cpp \
    Bullet/BulletCollision/CollisionShapes/btMultiSphereShape.cpp \
    Bullet/BulletCollision/CollisionShapes/btBvhTriangleMeshShape.cpp \
    Bullet/BulletCollision/CollisionShapes/btStridingMeshInterface.cpp \
    Bullet/BulletCollision/Gimpact/btGImpactCollisionAlgorithm.cpp \
    Bullet/BulletCollision/CollisionShapes/btCollisionShape.cpp \
    Bullet/BulletCollision/NarrowPhaseCollision/btSubSimplexConvexCast.cpp \
    Bullet/BulletDynamics/ConstraintSolver/btUniversalConstraint.cpp \
    Bullet/LinearMath/btSerializer.cpp \
    Bullet/BulletCollision/CollisionDispatch/btInternalEdgeUtility.cpp \
    Bullet/BulletDynamics/ConstraintSolver/btHinge2Constraint.cpp \
    Bullet/BulletDynamics/ConstraintSolver/btGeneric6DofSpringConstraint.cpp \
    Bullet/BulletCollision/CollisionShapes/btConvex2dShape.cpp \
    Bullet/BulletCollision/CollisionDispatch/btConvex2dConvex2dAlgorithm.cpp \
    Bullet/BulletCollision/CollisionShapes/btBox2dShape.cpp \
    Bullet/BulletCollision/CollisionDispatch/btBox2dBox2dCollisionAlgorithm.cpp \
    Bullet/BulletCollision/BroadphaseCollision/btDbvt.cpp \
    Bullet/BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.cpp \
    Bullet/BulletCollision/CollisionShapes/btConvexHullShape.cpp \
    Bullet/BulletCollision/CollisionDispatch/btCompoundCollisionAlgorithm.cpp \
    Bullet/BulletCollision/CollisionDispatch/btCollisionObject.cpp \
    Bullet/BulletDynamics/Dynamics/btRigidBody.cpp \
    Bullet/BulletCollision/CollisionDispatch/btUnionFind.cpp \
    Bullet/BulletCollision/CollisionDispatch/btSimulationIslandManager.cpp \
    Bullet/BulletCollision/CollisionShapes/btCompoundShape.cpp \
    Bullet/BulletDynamics/Character/btKinematicCharacterController.cpp \
    Bullet/BulletDynamics/ConstraintSolver/btHingeConstraint.cpp \
    Bullet/BulletCollision/Gimpact/gim_tri_collision.cpp \
    Bullet/BulletCollision/Gimpact/btTriangleShapeEx.cpp \
    Bullet/BulletCollision/Gimpact/btGImpactQuantizedBvh.cpp \
    Bullet/BulletCollision/Gimpact/btGImpactBvh.cpp \
    Bullet/BulletCollision/Gimpact/btGenericPoolAllocator.cpp \
    Bullet/BulletDynamics/Dynamics/btDiscreteDynamicsWorld.cpp \
    Bullet/BulletDynamics/ConstraintSolver/btPoint2PointConstraint.cpp \
    Bullet/BulletCollision/CollisionDispatch/btConvexConvexAlgorithm.cpp \
    Bullet/BulletCollision/CollisionDispatch/btCollisionWorld.cpp \
    Bullet/BulletDynamics/ConstraintSolver/btTypedConstraint.cpp \
    Bullet/BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.cpp \
    Bullet/BulletDynamics/Vehicle/btRaycastVehicle.cpp \
    Bullet/BulletCollision/CollisionDispatch/btBoxBoxDetector.cpp \
    Bullet/LinearMath/btQuickprof.cpp \
    Bullet/LinearMath/btAlignedAllocator.cpp \
    Views/OpenGL/Camera.cpp \
    Views/OpenGL/GLWidget_1.cpp \
    main.cpp \
    Views/MainWindow.cpp \
    Views/OpenGL/GLCreatureViewer.cpp \
    World/BasicShapes/Surface.cpp \
    World/BasicShapes/Sphere.cpp \
    World/BasicShapes/Box.cpp \
    generic6dofconstraintcontroller.cpp

HEADERS  += \
    Bullet/LinearMath/btRandom.h \
    Bullet/LinearMath/btList.h \
    Bullet/BulletCollision/NarrowPhaseCollision/btSubSimplexConvexCast.h \
    Bullet/BulletCollision/NarrowPhaseCollision/btContinuousConvexCollision.h \
    Bullet/BulletDynamics/ConstraintSolver/btSolve2LinearConstraint.h \
    Bullet/BulletCollision/NarrowPhaseCollision/btGjkConvexCast.h \
    Bullet/BulletDynamics/Dynamics/btContinuousDynamicsWorld.h \
    Bullet/BulletDynamics/ConstraintSolver/btConstraintSolver.h \
    Bullet/BulletCollision/CollisionDispatch/btEmptyCollisionAlgorithm.h \
    Bullet/BulletCollision/BroadphaseCollision/btCollisionAlgorithm.h \
    Bullet/BulletCollision/BroadphaseCollision/btOverlappingPairCallback.h \
    Bullet/BulletCollision/NarrowPhaseCollision/btSimplexSolverInterface.h \
    Bullet/BulletCollision/CollisionDispatch/btCollisionConfiguration.h \
    Bullet/LinearMath/btAabbUtil2.h \
    Bullet/BulletCollision/CollisionDispatch/btConvexConcaveCollisionAlgorithm.h \
    Bullet/LinearMath/btQuadWord.h \
    Bullet/BulletCollision/CollisionDispatch/btCompoundCollisionAlgorithm.h \
    Bullet/BulletDynamics/Vehicle/btVehicleRaycaster.h \
    Bullet/LinearMath/btStackAlloc.h \
    Bullet/BulletCollision/CollisionDispatch/btSphereTriangleCollisionAlgorithm.h \
    Bullet/BulletCollision/CollisionDispatch/btSphereSphereCollisionAlgorithm.h \
    Bullet/BulletCollision/CollisionDispatch/btSphereBoxCollisionAlgorithm.h \
    Bullet/BulletCollision/CollisionDispatch/btSimulationIslandManager.h \
    Bullet/LinearMath/btMotionState.h \
    Bullet/LinearMath/btGeometryUtil.h \
    Bullet/BulletCollision/CollisionDispatch/btCollisionCreateFunc.h \
    Bullet/BulletCollision/CollisionDispatch/btBoxBoxDetector.h \
    Bullet/BulletCollision/CollisionDispatch/btBoxBoxCollisionAlgorithm.h \
    Bullet/LinearMath/btAlignedAllocator.h \
    Bullet/BulletCollision/CollisionDispatch/btActivatingCollisionAlgorithm.h \
    Bullet/BulletCollision/NarrowPhaseCollision/btRaycastCallback.h \
    Bullet/Bullet-C-Api.h \
    Bullet/BulletCollision/CollisionDispatch/btConvexPlaneCollisionAlgorithm.h \
    Bullet/BulletCollision/CollisionShapes/btUniformScalingShape.h \
    Bullet/BulletCollision/CollisionShapes/btTriangleIndexVertexMaterialArray.h \
    Bullet/BulletCollision/CollisionShapes/btTriangleCallback.h \
    Bullet/BulletCollision/CollisionShapes/btTriangleBuffer.h \
    Bullet/BulletCollision/CollisionShapes/btSphereShape.h \
    Bullet/BulletCollision/CollisionShapes/btScaledBvhTriangleMeshShape.h \
    Bullet/BulletCollision/CollisionShapes/btMinkowskiSumShape.h \
    Bullet/BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h \
    Bullet/BulletCollision/CollisionShapes/btEmptyShape.h \
    Bullet/BulletCollision/CollisionShapes/btConvexShape.h \
    Bullet/BulletCollision/CollisionShapes/btConeShape.h \
    Bullet/BulletCollision/CollisionShapes/btConcaveShape.h \
    Bullet/BulletCollision/CollisionShapes/btCollisionMargin.h \
    Bullet/btBulletDynamicsCommon.h \
    Bullet/BulletCollision/CollisionShapes/btTetrahedronShape.h \
    Bullet/BulletCollision/CollisionShapes/btPolyhedralConvexShape.h \
    Bullet/BulletCollision/CollisionShapes/btConvexTriangleMeshShape.h \
    Bullet/BulletCollision/BroadphaseCollision/btMultiSapBroadphase.h \
    Bullet/BulletCollision/NarrowPhaseCollision/btConvexCast.h \
    Bullet/BulletDynamics/Character/btCharacterControllerInterface.h \
    Bullet/BulletDynamics/Dynamics/btSimpleDynamicsWorld.h \
    Bullet/BulletCollision/CollisionShapes/btTriangleMesh.h \
    Bullet/BulletDynamics/ConstraintSolver/btJacobianEntry.h \
    Bullet/BulletCollision/NarrowPhaseCollision/btGjkPairDetector.h \
    Bullet/BulletCollision/NarrowPhaseCollision/btGjkEpaPenetrationDepthSolver.h \
    Bullet/BulletCollision/CollisionShapes/btConvexPointCloudShape.h \
    Bullet/BulletCollision/NarrowPhaseCollision/btConvexPenetrationDepthSolver.h \
    Bullet/BulletCollision/CollisionShapes/btTriangleIndexVertexArray.h \
    Bullet/BulletCollision/NarrowPhaseCollision/btPointCollector.h \
    Bullet/BulletCollision/NarrowPhaseCollision/btGjkEpa2.h \
    Bullet/BulletCollision/NarrowPhaseCollision/btDiscreteCollisionDetectorInterface.h \
    Bullet/BulletDynamics/Dynamics/btDynamicsWorld.h \
    Bullet/BulletCollision/CollisionShapes/btTriangleShape.h \
    Bullet/LinearMath/btQuaternion.h \
    Bullet/LinearMath/btDefaultMotionState.h \
    Views/OpenGL/geometrie.h \
    Bullet/BulletCollision/CollisionDispatch/btConvexConvexAlgorithm.h \
    Bullet/BulletDynamics/Vehicle/btWheelInfo.h \
    Bullet/BulletCollision/BroadphaseCollision/btOverlappingPairCache.h \
    Bullet/LinearMath/btConvexHull.h \
    Bullet/BulletCollision/CollisionShapes/btMaterial.h \
    Bullet/BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h \
    Bullet/LinearMath/btTransform.h \
    Bullet/BulletCollision/CollisionShapes/btMultiSphereShape.h \
    Bullet/LinearMath/btMatrix3x3.h \
    Bullet/BulletCollision/CollisionShapes/btConvexInternalShape.h \
    Bullet/BulletCollision/CollisionShapes/btConvexHullShape.h \
    Bullet/btBulletCollisionCommon.h \
    Bullet/BulletCollision/Gimpact/btGImpactShape.h \
    Bullet/BulletCollision/CollisionShapes/btBoxShape.h \
    Bullet/BulletCollision/CollisionShapes/btMultimaterialTriangleMeshShape.h \
    Bullet/BulletCollision/CollisionShapes/btShapeHull.h \
    Bullet/BulletCollision/NarrowPhaseCollision/btMinkowskiPenetrationDepthSolver.h \
    Bullet/BulletCollision/BroadphaseCollision/btDbvt.h \
    Bullet/BulletCollision/CollisionDispatch/btManifoldResult.h \
    Bullet/BulletCollision/BroadphaseCollision/btSimpleBroadphase.h \
    Bullet/BulletCollision/BroadphaseCollision/btDbvtBroadphase.h \
    Bullet/BulletCollision/BroadphaseCollision/btBroadphaseInterface.h \
    Bullet/BulletCollision/BroadphaseCollision/btAxisSweep3.h \
    Bullet/BulletDynamics/ConstraintSolver/btSolverBody.h \
    Bullet/BulletDynamics/ConstraintSolver/btSliderConstraint.h \
    Bullet/BulletDynamics/ConstraintSolver/btPoint2PointConstraint.h \
    Bullet/BulletDynamics/ConstraintSolver/btContactConstraint.h \
    Bullet/BulletDynamics/ConstraintSolver/btConeTwistConstraint.h \
    Bullet/BulletCollision/CollisionShapes/btStaticPlaneShape.h \
    Bullet/BulletCollision/CollisionShapes/btCapsuleShape.h \
    Bullet/BulletCollision/CollisionShapes/btTriangleMeshShape.h \
    Bullet/BulletCollision/CollisionShapes/btOptimizedBvh.h \
    Bullet/BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.h \
    Bullet/BulletCollision/NarrowPhaseCollision/btVoronoiSimplexSolver.h \
    Bullet/BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h \
    Bullet/BulletCollision/CollisionDispatch/SphereTriangleDetector.h \
    Bullet/BulletCollision/CollisionShapes/btBvhTriangleMeshShape.h \
    Bullet/BulletCollision/BroadphaseCollision/btQuantizedBvh.h \
    Bullet/BulletCollision/CollisionShapes/btStridingMeshInterface.h \
    Bullet/BulletCollision/CollisionShapes/btCollisionShape.h \
    Bullet/BulletCollision/BroadphaseCollision/btBroadphaseProxy.h \
    Bullet/BulletDynamics/ConstraintSolver/btUniversalConstraint.h \
    Bullet/BulletCollision/CollisionShapes/btTriangleInfoMap.h \
    Bullet/BulletDynamics/Vehicle/btRaycastVehicle.h \
    Bullet/BulletCollision/CollisionDispatch/btInternalEdgeUtility.h \
    Bullet/BulletDynamics/ConstraintSolver/btHinge2Constraint.h \
    Bullet/BulletDynamics/ConstraintSolver/btGeneric6DofSpringConstraint.h \
    Bullet/BulletCollision/CollisionShapes/btConvex2dShape.h \
    Bullet/BulletCollision/CollisionDispatch/btConvex2dConvex2dAlgorithm.h \
    Bullet/BulletCollision/CollisionShapes/btBox2dShape.h \
    Bullet/BulletCollision/CollisionDispatch/btBox2dBox2dCollisionAlgorithm.h \
    Bullet/BulletDynamics/ConstraintSolver/btHingeConstraint.h \
    Bullet/BulletCollision/CollisionShapes/btCompoundShape.h \
    Bullet/BulletCollision/CollisionDispatch/btCollisionDispatcher.h \
    Bullet/LinearMath/btPoolAllocator.h \
    Bullet/LinearMath/btMinMax.h \
    Bullet/BulletCollision/NarrowPhaseCollision/btManifoldPoint.h \
    Bullet/LinearMath/btAlignedObjectArray.h \
    Bullet/BulletCollision/CollisionShapes/btCylinderShape.h \
    Bullet/BulletCollision/CollisionDispatch/btUnionFind.h \
    Bullet/BulletDynamics/ConstraintSolver/btSolverConstraint.h \
    Bullet/LinearMath/btHashMap.h \
    Bullet/BulletCollision/CollisionDispatch/btGhostObject.h \
    Bullet/BulletDynamics/Character/btKinematicCharacterController.h \
    Bullet/BulletCollision/NarrowPhaseCollision/btPersistentManifold.h \
    Bullet/LinearMath/btIDebugDraw.h \
    Bullet/BulletCollision/Gimpact/gim_tri_collision.h \
    Bullet/BulletCollision/Gimpact/gim_radixsort.h \
    Bullet/BulletCollision/Gimpact/gim_memory.h \
    Bullet/BulletCollision/Gimpact/gim_math.h \
    Bullet/BulletCollision/Gimpact/gim_linear_math.h \
    Bullet/BulletCollision/Gimpact/gim_hash_table.h \
    Bullet/BulletCollision/Gimpact/gim_geometry.h \
    Bullet/BulletCollision/Gimpact/gim_geom_types.h \
    Bullet/BulletCollision/Gimpact/gim_contact.h \
    Bullet/BulletCollision/Gimpact/gim_clip_polygon.h \
    Bullet/BulletCollision/Gimpact/gim_box_set.h \
    Bullet/BulletCollision/Gimpact/gim_box_collision.h \
    Bullet/BulletCollision/Gimpact/gim_bitset.h \
    Bullet/BulletCollision/Gimpact/gim_basic_geometry_operations.h \
    Bullet/BulletCollision/Gimpact/gim_array.h \
    Bullet/BulletCollision/Gimpact/btTriangleShapeEx.h \
    Bullet/BulletCollision/Gimpact/btQuantization.h \
    Bullet/BulletCollision/Gimpact/btGImpactQuantizedBvh.h \
    Bullet/BulletCollision/Gimpact/btGImpactMassUtil.h \
    Bullet/BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h \
    Bullet/BulletCollision/Gimpact/btGImpactBvh.h \
    Bullet/BulletCollision/Gimpact/btGeometryOperations.h \
    Bullet/BulletCollision/Gimpact/btGenericPoolAllocator.h \
    Bullet/BulletCollision/Gimpact/btContactProcessing.h \
    Bullet/BulletCollision/Gimpact/btClipPolygon.h \
    Bullet/BulletCollision/Gimpact/btBoxCollision.h \
    Bullet/LinearMath/btScalar.h \
    Bullet/BulletDynamics/Dynamics/btRigidBody.h \
    Bullet/BulletCollision/CollisionDispatch/btCollisionObject.h \
    Bullet/BulletCollision/CollisionDispatch/btCollisionWorld.h \
    Bullet/LinearMath/btSerializer.h \
    Bullet/BulletDynamics/ConstraintSolver/btContactSolverInfo.h \
    Bullet/BulletCollision/BroadphaseCollision/btDispatcher.h \
    Bullet/LinearMath/btTransformUtil.h \
    Bullet/BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h \
    Bullet/BulletDynamics/Dynamics/btActionInterface.h \
    Bullet/BulletDynamics/ConstraintSolver/btTypedConstraint.h \
    Bullet/LinearMath/btVector3.h \
    Bullet/LinearMath/btQuickprof.h \
    Views/OpenGL/Camera.h \
    World/Drawable.h \
    Views/MainWindow.h \
    Views/OpenGL/GLWidget_1.h \
    World/Human.h \
    Views/OpenGL/GLCreatureViewer.h \
    World/Snake.h \
    World/Constraints/PointToPointConstraint.h \
    World/BasicShapes/Surface.h \
    World/BasicShapes/Sphere.h \
    World/BasicShapes/Box.h \
    World/BasicShapes/Axis.h \
    World/Constraints/HingeConstraint.h \
    World/Arm.h \
    World/Constraints/ConeTwistConstraint.h \
    World/BasicShapes/drawablevector.h \
    generic6dofconstraintcontroller.h \
    World/motorisedArm.h

OTHER_FILES +=

FORMS += \
    Views/mainwindow.ui \
    generic6dofconstraintcontroller.ui