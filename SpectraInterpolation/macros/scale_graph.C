// this scales a graph
// and its errors, if appropriate 
// there are two versions, one which outputs a new scaled graph,
// the other modifies the original graph, so be careful

#ifndef _SCALE_GRAPH_
#define _SCALE_GRAPH_

#include "TGraph.h"
#include "TGraphErrors.h"

Int_t scale_graph(TGraph *graph, Float_t factor)
{
  //printf("Scaling graph %s by factor %f\n",graph->GetName(),factor);
  Double_t x,y;
  for(Int_t ipoint=0;ipoint<graph->GetN();ipoint++) {

    graph->GetPoint(ipoint,x,y);
    //printf("Point %d: x = %f; y = %f\n",ipoint,x,y);
    // scale the y point
    graph->SetPoint(ipoint,x,y*factor);
  }

  return 0;
}

Int_t scale_graph(TGraphErrors *graph, Float_t factor)
{
  //printf("Scaling graph %s by factor %f\n",graph->GetName(),factor);
  Double_t x,y;
  for(Int_t ipoint=0;ipoint<graph->GetN();ipoint++) {

    graph->GetPoint(ipoint,x,y);
    //printf("Point %d: x = %f; y = %f\n",ipoint,x,y);
    // scale the y point
    graph->SetPoint(ipoint,x,y*factor);
    // must scale errors also since this is a TgraphErrors
    Float_t errx = graph->GetErrorX(ipoint);
    Float_t erry = factor*graph->GetErrorY(ipoint);
    
    graph->SetPointError(ipoint,errx,erry);
  }

  return 0;
}

#endif
