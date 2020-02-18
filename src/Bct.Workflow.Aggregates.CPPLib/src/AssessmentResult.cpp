#include "AssessmentResult.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         AssessmentResult::AssessmentResult()
         {

         }
         void AssessmentResult::addError(std::string id, std::string context)
         {
            _ids.push_back(id);
            _contexts.push_back(context);
         }
         std::vector<std::string> AssessmentResult::getErrorIds()
         {
            return _ids;
         }
         std::vector<std::string> AssessmentResult::getContexts()
         {
            return _contexts;
         }
         bool AssessmentResult::isSuccess()
         {
            return _ids.size() == 0;
         }
         bool AssessmentResult::isFailure()
         {
            return _ids.size() != 0;
         }
      }
   }
}
