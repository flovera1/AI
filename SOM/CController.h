#ifndef CCONTROLLER_H
#define CCONTROLLER_H


//------------------------------------------------------------------------
//
//  Name:   CController.h
//
//  Desc:   controller class for the SOM demo
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------

#include <windows.h>
#include <vector>

using namespace std;

#include "CNode.h"
#include "Csom.h"
#include "constants.h"


class CController
{

private:

  //pointer to a Self Organising Map
  Csom*                   m_pSOM;

  //the data for the training
  vector<vector<double> > m_TrainingSet;


  //this method creates a small data set of color values
  //that are used to train the network with
  void CreateDataSet();


public:

  CController(int cxClient, int cyClient, int CellsUp, int CellsAcross, int NumIterations)
  {
    //create the SOM
    m_pSOM = new Csom();

    m_pSOM->Create(cxClient, cyClient, CellsUp, CellsAcross, NumIterations);

    //create the training set
    CreateDataSet();
  }
      
  ~CController()
  {
    delete m_pSOM;
  }

  void Render(HDC surface);

  bool Train();

  bool Finished()const{return m_pSOM->FinishedTraining();}



};


#endif