#ifndef PANZER_EQUATION_SET_FACTORY_HPP
#define PANZER_EQUATION_SET_FACTORY_HPP

#include "Teuchos_RCP.hpp"
#include "Panzer_Traits.hpp"
#include "Panzer_InputEquationSet.hpp"
#include "Panzer_CellData.hpp"
#include "Panzer_EquationSet_TemplateManager.hpp"
#include "Panzer_GlobalData.hpp"

namespace panzer {

  struct EquationSetFactory {

    virtual Teuchos::RCP<panzer::EquationSet_TemplateManager<panzer::Traits> >
    buildEquationSet(const panzer::InputEquationSet& ies,
		     const panzer::CellData& cell_data,
		     const Teuchos::RCP<panzer::GlobalData>& global_data,
		     bool build_transient_support) const = 0;

  };
  
}

#endif
