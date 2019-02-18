#include "student_code.h"
#include "mutablePriorityQueue.h"

using namespace std;

namespace CGL
{
  void BezierCurve::evaluateStep()
  {
    //Part 1.
    // Perform one step of the Bezier curve's evaluation at t using de Casteljau's algorithm for subdivision.
    // Store all of the intermediate control points into the 2D vector evaluatedLevels.
    int levels = evaluatedLevels.size();
    vector<Vector2D> most_recent_points = evaluatedLevels[levels - 1];
    if (most_recent_points.size() == 1) { //check the most recent levels, if there's only one control points, then we're done
        return;
    } else {
        vector<Vector2D> new_points;
        for (int i = 0; i < most_recent_points.size() - 1; i++) {
            Vector2D p1 = most_recent_points[i];
            Vector2D p2 = most_recent_points[i + 1];
            new_points.push_back(Vector2D((1 - t) * p1 + t * p2));
        }
        evaluatedLevels.push_back(new_points);
    }
    return;
  }


  Vector3D BezierPatch::evaluate(double u, double v) const
  {
    // TODO Part 2.
    // Evaluate the Bezier surface at parameters (u, v) through 2D de Casteljau subdivision.
    // (i.e. Unlike Part 1 where we performed one subdivision level per call to evaluateStep, this function
    // should apply de Casteljau's algorithm until it computes the final, evaluated point on the surface)

    vector<Vector3D> curves;

    for (int i = 0; i < controlPoints.size(); i++) { //deal with 1D de Casteljau first.
        curves.push_back(evaluate1D(controlPoints[i], u));
    }

    return evaluate1D(curves, v);
  }

  Vector3D BezierPatch::evaluate1D(std::vector<Vector3D> points, double t) const
  {
    // TODO Part 2.
    // Optional helper function that you might find useful to implement as an abstraction when implementing BezierPatch::evaluate.
    // Given an array of 4 points that lie on a single curve, evaluates the Bezier curve at parameter t using 1D de Casteljau subdivision.
    vector<Vector3D> temp1; //3 points
    vector<Vector3D> temp2; //2 points

    for (int i = 0; i < points.size() - 1; i++) {
        Vector3D p1 = points[i];
        Vector3D p2 = points[i + 1];
        temp1.push_back(Vector3D((1 - t) * p1 + t * p2));
    }

  for (int i = 0; i < temp1.size() - 1; i++) {
      Vector3D p1 = temp1[i];
      Vector3D p2 = temp1[i + 1];
      temp2.push_back(Vector3D((1 - t) * p1 + t * p2));
  }

  return Vector3D((1 - t) * temp2[0] + t * temp2[1]);
 }



  Vector3D Vertex::normal( void ) const
  {
    // TODO Part 3.
    // TODO Returns an approximate unit normal at this vertex, computed by
    // TODO taking the area-weighted average of the normals of neighboring
    // TODO triangles, then normalizing.
    Vector3D n(0,0,0);
    HalfedgeCIter h = halfedge(); //get the half Edge corresponding to this vertex.
    h = h -> twin();
    HalfedgeCIter h_orig = h; //save the pointer to the original half edge.

    do {
        FaceCIter f = h -> face();
        n += f -> normal(); //store the normalized value of a triangle to n.
        h = h -> next() -> twin();
    } while (h != h_orig); //iterating until we go back to h_orig
    return n.unit();
  }

  EdgeIter HalfedgeMesh::flipEdge( EdgeIter e0 )
  {
    // TODO Part 4.
    // TODO This method should flip the given edge and return an iterator to the flipped edge.
    return e0;
  }

  VertexIter HalfedgeMesh::splitEdge( EdgeIter e0 )
  {
    // TODO Part 5.
    // TODO This method should split the given edge and return an iterator to the newly inserted vertex.
    // TODO The halfedge of this vertex should point along the edge that was split, rather than the new edges.
    return newVertex();
  }



  void MeshResampler::upsample( HalfedgeMesh& mesh )
  {
    // TODO Part 6.
    // This routine should increase the number of triangles in the mesh using Loop subdivision.
    // Each vertex and edge of the original surface can be associated with a vertex in the new (subdivided) surface.
    // Therefore, our strategy for computing the subdivided vertex locations is to *first* compute the new positions
    // using the connectity of the original (coarse) mesh; navigating this mesh will be much easier than navigating
    // the new subdivided (fine) mesh, which has more elements to traverse. We will then assign vertex positions in
    // the new mesh based on the values we computed for the original mesh.


    // TODO Compute new positions for all the vertices in the input mesh, using the Loop subdivision rule,
    // TODO and store them in Vertex::newPosition. At this point, we also want to mark each vertex as being
    // TODO a vertex of the original mesh.


    // TODO Next, compute the updated vertex positions associated with edges, and store it in Edge::newPosition.


    // TODO Next, we're going to split every edge in the mesh, in any order.  For future
    // TODO reference, we're also going to store some information about which subdivided
    // TODO edges come from splitting an edge in the original mesh, and which edges are new,
    // TODO by setting the flat Edge::isNew.  Note that in this loop, we only want to iterate
    // TODO over edges of the original mesh---otherwise, we'll end up splitting edges that we
    // TODO just split (and the loop will never end!)


    // TODO Now flip any new edge that connects an old and new vertex.


    // TODO Finally, copy the new vertex positions into final Vertex::position.

    return;
  }
}
