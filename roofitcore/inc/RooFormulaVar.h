/*****************************************************************************
 * Project: BaBar detector at the SLAC PEP-II B-factory
 * Package: RooFitCore
 *    File: $Id: RooFormulaVar.rdl,v 1.12 2001/09/20 01:40:10 verkerke Exp $
 * Authors:
 *   DK, David Kirkby, Stanford University, kirkby@hep.stanford.edu
 *   WV, Wouter Verkerke, UC Santa Barbara, verkerke@slac.stanford.edu
 * History:
 *   07-Mar-2001 WV Created initial version
 *
 * Copyright (C) 2001 University of California
 *****************************************************************************/
#ifndef ROO_FORMULA_VAR
#define ROO_FORMULA_VAR

#include "RooFitCore/RooAbsReal.hh"
#include "RooFitCore/RooFormula.hh"

class RooArgSet ;

class RooFormulaVar : public RooAbsReal {
public:
  // Constructors, assignment etc
  inline RooFormulaVar() { }
  RooFormulaVar(const char *name, const char *title, const char* formula, const RooArgSet& dependents);
  RooFormulaVar(const char *name, const char *title, const RooArgSet& dependents);
  RooFormulaVar(const RooFormulaVar& other, const char* name=0);
  virtual TObject* clone(const char* newname) const { return new RooFormulaVar(*this,newname); }
  virtual ~RooFormulaVar();

  // Formula editing interface
  Bool_t setFormula(const char* formula) ;
  inline Bool_t ok() const { return _formula.ok() ; }

  inline RooAbsArg* getParameter(const char* name) const { return _formula.getParameter(name) ; }
  inline RooAbsArg* getParameter(Int_t index) const { return _formula.getParameter(index) ; }

  // I/O streaming interface (machine readable)
  virtual Bool_t readFromStream(istream& is, Bool_t compact, Bool_t verbose=kFALSE) ;
  virtual void writeToStream(ostream& os, Bool_t compact) const ;

  // Printing interface (human readable)
  virtual void printToStream(ostream& os, PrintOption opt=Standard, TString indent= "") const ;

  // Custom dependent checking
  virtual Bool_t checkDependents(const RooArgSet* nset) const ;

  // Debugging
  void dumpFormula() { _formula.dump() ; }

  // In general, we cannot be normalized sensibly so pretend that we are always normalized
  Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& numVars, const RooArgSet* normSet) const ;
  Double_t analyticalIntegral(Int_t code, const RooArgSet* normSet) const ;
  //inline Bool_t selfNormalized() const { return kTRUE; }

protected:

  // Function evaluation
  virtual Double_t evaluate() const ;

  // Post-processing of server redirection
  virtual Bool_t redirectServersHook(const RooAbsCollection& newServerList, Bool_t mustReplaceAll=kFALSE) ;

  virtual Bool_t isValidReal(Double_t value, Bool_t printError) const ;

  mutable RooFormula _formula ; // Formula engine 

  ClassDef(RooFormulaVar,1) // Real-valued variable, calculated from a string expression formula 
};

#endif
