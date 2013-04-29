#ifndef _DIVIDE_GRAPH_BY_FUNCTION_
#define _DIVIDE_GRAPH_BY_FUNCTION_

#include "TGraph.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TSpline.h"

// divide graph by a TF1 and output a new graph
// there's also an overloaded version for a TGraphErrors too
// the TGraphErrors version scales the error output 

TGraph* divide_graph_by_function(TGraph *graph, TF1 *fn, Bool_t inv=kFALSE)
{
  TGraph *div_graph = new TGraph();
  div_graph->Set(graph->GetN());

  for(Int_t i=0;i<graph->GetN();i++) {
	  Double_t x, y;
	  graph->GetPoint(i,x,y);
	  if(inv) {
		  if(y==0) div_graph->SetPoint(i,x,0);
		  else div_graph->SetPoint(i,x,fn->Eval(x)/y);
	  } else {
		  div_graph->SetPoint(i,x,y/fn->Eval(x));
	  }
  }

  // copy styles
  div_graph->SetMarkerStyle(graph->GetMarkerStyle());
  div_graph->SetMarkerColor(graph->GetMarkerColor());

  return div_graph;
}

TGraph* divide_graph_by_function(TGraph *graph, TSpline *fn, Bool_t inv=kFALSE)
{
	TGraph *div_graph = new TGraph();
	div_graph->Set(graph->GetN());
	
	for(Int_t i=0;i<graph->GetN();i++) {
		Double_t x, y, y_new;
		graph->GetPoint(i,x,y);
		if(fn->Eval(x)>0) y_new = y/fn->Eval(x);
		else y_new=0.0;
		div_graph->SetPoint(i,x,y_new);
		
	}
	
	// copy styles
	div_graph->SetMarkerStyle(graph->GetMarkerStyle());
	div_graph->SetMarkerColor(graph->GetMarkerColor());
	
	return div_graph;
}

TGraphErrors* divide_graph_by_function(TGraphErrors *graph, TF1 *fn, Bool_t inv=kFALSE)
{
  TGraphErrors *div_graph = new TGraphErrors();
  div_graph->Set(graph->GetN());

  // scales the y error on output graph
  // x err is untouched

  for(Int_t i=0;i<graph->GetN();i++) {
    Double_t x, y, x_err, y_err;
    graph->GetPoint(i,x,y);
    x_err = graph->GetErrorX(i);
    y_err = graph->GetErrorY(i);
    Double_t y_new, y_err_new;
    if(fn->Eval(x)>0) y_new = y/fn->Eval(x);
	else y_new=0.0;
    // keep same relative error on new point
    if(y>0)  y_err_new = y_new*(y_err/y);
	else y_err_new = 0.0;
    div_graph->SetPoint(i,x,y_new);
    div_graph->SetPointError(i,x_err,y_err_new);
  }

  // copy styles
  div_graph->SetMarkerStyle(graph->GetMarkerStyle());
  div_graph->SetMarkerColor(graph->GetMarkerColor());

  return div_graph;
}

TGraphErrors* divide_graph_by_function(TGraphErrors *graph, TSpline *fn, Bool_t inv=kFALSE)
{
	TGraphErrors *div_graph = new TGraphErrors();
	div_graph->Set(graph->GetN());
	
	// scales the y error on output graph
	// x err is untouched
	
	for(Int_t i=0;i<graph->GetN();i++) {
		Double_t x, y, x_err, y_err;
		graph->GetPoint(i,x,y);
		x_err = graph->GetErrorX(i);
		y_err = graph->GetErrorY(i);
		Double_t y_new, y_err_new;
		if(fn->Eval(x)>0) y_new = y/fn->Eval(x);
		else y_new=0.0;
		// keep same relative error on new point
		if(y>0)  y_err_new = y_new*(y_err/y);
		else y_err_new = 0.0;
		div_graph->SetPoint(i,x,y_new);
		div_graph->SetPointError(i,x_err,y_err_new);
	}
	
	// copy styles
	div_graph->SetMarkerStyle(graph->GetMarkerStyle());
	div_graph->SetMarkerColor(graph->GetMarkerColor());
	
	return div_graph;
}


#endif
