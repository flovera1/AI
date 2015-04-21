#include "Csom.h"


void Csom::Create(int cxClient,
                  int cyClient,
                  int CellsUp,
                  int CellsAcross,
                  int NumIterations)
{

  m_dCellWidth  = (double)cxClient / (double)CellsAcross;

  m_dCellHeight = (double)cyClient / (double)CellsUp;

  m_iNumIterations = NumIterations;
  
  //create all the nodes
  for (int row=0; row<CellsUp; ++row)
  {
    for (int col=0; col<CellsAcross; ++col)
    {
      m_SOM.push_back(CNode(col*m_dCellWidth,           //left
                            (col+1)*m_dCellWidth,       //right
                            row*m_dCellHeight,          //top
                            (row+1)*m_dCellHeight,      //bottom
                            constSizeOfInputVector));   //num weights
    }
  }

  //this is the topological 'radius' of the feature map
  m_dMapRadius = max(constWindowWidth, constWindowHeight)/2;

   //used in the calculation of the neighbourhood width of m_dInfluence
  m_dTimeConstant = m_iNumIterations/log(m_dMapRadius);
}  

//---------------------------- Render ------------------------------------
//
//------------------------------------------------------------------------
void Csom::Render(HDC surface)
{
  //render all the cells
  for (int nd=0; nd<m_SOM.size(); ++nd)
  {
    m_SOM[nd].Render(surface);
    
  }

  SetBkMode(surface, TRANSPARENT);
  SetTextColor(surface, RGB(255,255,255));
  
  string s = "Iteration: " + itos(m_iIterationCount);
  TextOut(surface, 5, constWindowHeight - 40, s.c_str(), s.size());

  s = "Press 'R' to retrain";
  TextOut(surface, 260, constWindowHeight - 40, s.c_str(), s.size());

/*
  s = "Learning: " + ftos(m_dLearningRate);
  TextOut(surface, 5, 20, s.c_str(), s.size());

  s = "Radius: " + ftos(m_dNeighbourhoodRadius);
  TextOut(surface, 5, 40, s.c_str(), s.size());
*/
}
              
      
//--------------------------- Epoch --------------------------------------
//
//  Given a std::vector of input vectors this method choses one at random
//  and runs the network through one training epoch
//------------------------------------------------------------------------
bool Csom::Epoch(const vector<vector<double> > &data)
{
  //make sure the size of the input vector matches the size of each node's 
  //weight vector
  if (data[0].size() != constSizeOfInputVector) return false;

  //return if the training is complete
  if (m_bDone) return true;
 
  
  //enter the training loop
  if (--m_iNumIterations > 0)
  {
    //the input vectors are presented to the network at random
    int ThisVector = RandInt(0, data.size()-1);

    //present the vector to each node and determine the BMU
    m_pWinningNode = FindBestMatchingNode(data[ThisVector]);

    //calculate the width of the neighbourhood for this timestep
    m_dNeighbourhoodRadius = m_dMapRadius * exp(-(double)m_iIterationCount/m_dTimeConstant);

    //Now to adjust the weight vector of the BMU and its
    //neighbours

    //For each node calculate the m_dInfluence (Theta from equation 6 in
    //the tutorial. If it is greater than zero adjust the node's weights
    //accordingly
    for (int n=0; n<m_SOM.size(); ++n)
    {
      //calculate the Euclidean distance (squared) to this node from the
      //BMU
      double DistToNodeSq = (m_pWinningNode->X()-m_SOM[n].X()) *
                            (m_pWinningNode->X()-m_SOM[n].X()) +
                            (m_pWinningNode->Y()-m_SOM[n].Y()) *
                            (m_pWinningNode->Y()-m_SOM[n].Y()) ;

      double WidthSq = m_dNeighbourhoodRadius * m_dNeighbourhoodRadius;

      //if within the neighbourhood adjust its weights
      if (DistToNodeSq < (m_dNeighbourhoodRadius * m_dNeighbourhoodRadius))
      {

        //calculate by how much its weights are adjusted
        m_dInfluence = exp(-(DistToNodeSq) / (2*WidthSq));

        m_SOM[n].AdjustWeights(data[ThisVector],
                               m_dLearningRate,
                               m_dInfluence);
      }

    }//next node


    //reduce the learning rate
    m_dLearningRate = constStartLearningRate * exp(-(double)m_iIterationCount/m_iNumIterations);
    
    ++m_iIterationCount;

  }

  else
  {
    m_bDone = true;
  }

  return true;
}

//--------------------- CalculateBestMatchingNode ------------------------
//
//  this function presents an input vector to each node in the network
//  and calculates the Euclidean distance between the vectors for each
//  node. It returns a pointer to the best performer
//------------------------------------------------------------------------
CNode* Csom::FindBestMatchingNode(const vector<double> &vec)
{
  CNode* winner = NULL;

  double LowestDistance = 999999;
 
  for (int n=0; n<m_SOM.size(); ++n)
  {
    double dist = m_SOM[n].CalculateDistance(vec);

    if (dist < LowestDistance)
    {
      LowestDistance = dist;

      winner = &m_SOM[n];
    }
  }

  return winner;
}

