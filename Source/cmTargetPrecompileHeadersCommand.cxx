/*============================================================================
  CMake - Cross Platform Makefile Generator
  Copyright 2015 Daniel Pfeifer <purplekarrot@gmail.com>

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#include "cmTargetPrecompileHeadersCommand.h"

#include "cmGeneratorExpression.h"

//----------------------------------------------------------------------------
bool cmTargetPrecompileHeadersCommand
::InitialPass(std::vector<std::string> const& args, cmExecutionStatus &)
{
  return this->HandleArguments(args, "PRECOMPILE_HEADERS");
}

//----------------------------------------------------------------------------
void cmTargetPrecompileHeadersCommand
::HandleImportedTarget(const std::string &tgt)
{
  std::ostringstream e;
  e << "Cannot specify precompile headers for imported target \""
    << tgt << "\".";
  this->Makefile->IssueMessage(cmake::FATAL_ERROR, e.str());
}

//----------------------------------------------------------------------------
void cmTargetPrecompileHeadersCommand
::HandleMissingTarget(const std::string &name)
{
  std::ostringstream e;
  e << "Cannot specify precompile headers for target \"" << name << "\" "
       "which is not built by this project.";
  this->Makefile->IssueMessage(cmake::FATAL_ERROR, e.str());
}

//----------------------------------------------------------------------------
std::string cmTargetPrecompileHeadersCommand
::Join(const std::vector<std::string> &content)
{
  return cmJoin(content, ";");
}

//----------------------------------------------------------------------------
bool cmTargetPrecompileHeadersCommand
::HandleDirectContent(cmTarget *tgt, const std::vector<std::string> &content,
                      bool, bool)
{
  tgt->AppendProperty("PRECOMPILE_HEADERS", this->Join(content).c_str());
  return true;
}
