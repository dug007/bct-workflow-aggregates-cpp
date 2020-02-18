#include "NestedWithReference.h"
//#include "TPEPredictUserDataAggregate.h"

#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>

using namespace std;
using namespace rapidjson;
using namespace Bct::Workflow::Implementation;

static bool bSerialize( true ); // Perform de-serializtion if false.

#define CLOG cout<<__LINE__<<endl;

// parseArgs() is poor man's getopt() :)
static void parseArgs(int argc, char *argv[])
{
   for (std::size_t idx = 1; idx < argc; ++idx)
   {
      const std::string theArg = argv[idx];

      if( "-d" == theArg )
      {
         bSerialize = false;
         continue;
      }
   }
}

const string na_json =
"{ \
\"boolField\": true, \
\"int32Field\": -32, \
\"uint32Field\": 32, \
\"int64Field\":  60, \
\"uint64Field\": 64, \
\"doubleField\": 1.23, \
\"stringField\": \"hello world\", \
\"enumField\": 3, \
\"aggField\": { \
    \"boolField\": true, \
    \"int32Field\": -320, \
    \"uint32Field\": 320, \
    \"int64Field\": -640, \
    \"uint64Field\": 640, \
    \"doubleField\": -3.14, \
    \"stringField\": \"hello world - nested - na\", \
    \"boolFieldRequiredv2\": false, \
    \"enumField\": 4, \
    \"vectorIntField\": [20, 30, -50], \
    \"v100Field\": 100.0, \
    \"boolFieldRequiredv0\": false \
  } \
}";

const string ra_json =
"{ \
    \"boolField\": true, \
    \"int32Field\": -300, \
    \"uint32Field\": 320, \
    \"int64Field\": 60, \
    \"uint64Field\": 64000000000, \
    \"doubleField\": -7.8999999, \
    \"stringField\": \"hello world - nested - ra\", \
    \"boolFieldRequiredv2\": false, \
    \"enumField\": 40, \
    \"vectorIntField\": [2, 3, -5], \
    \"v100Field\": 100.0, \
    \"boolFieldRequiredv0\": true \
}";

const string tpe_json =
"{\
      \"gender\": null,\
      \"heightCm\" : null,\
      \"weightKg\" : null,\
      \"hctFrac\" : null,\
      \"tbvMl\" : null,\
      \"bmi\" : null,\
      \"patientHeightMinCm\" : 30.0,\
      \"patientHeightMaxCm\" : 244.0,\
      \"patientHeightMinEng\" : 12.0,\
      \"patientHeightMaxEng\" : 96.0,\
      \"patientWeightMin\" : 2.0,\
      \"patientWeightMax\" : 227.0,\
      \"patientWeightMinEng\" : 5.0,\
      \"patientWeightMaxEng\" : 500.0,\
      \"patientHCTMin\" : 0.1,\
      \"patientHCTMax\" : 0.7,\
      \"tBVLimitPercent\" : 0.15,\
      \"tBVEnteredMin\" : 300.0,\
      \"tBVEnteredMax\" : 15000.0,\
      \"tBVCalculationThresholdKg\" : 25.0,\
      \"bMIComputedMin\" : 0,\
      \"bMIComputedMax\" : 100\
}";

#define NA_TEST 1 // 1|0, respectively, to switch betw. NestedWithReferenceAggregate and ReferenceAggregate test.
#define TPE_TEST 0

static void runDeserialize( void )
{
#if NA_TEST
   #if TPE_TEST
   TPEPredictUserDataAggregate tpe;
   BaseAggregate *agg = &tpe;
   agg->deserialize(tpe_json);
   #else
      NestedWithReferenceAggregate na;
      BaseAggregate *agg = &na;
      agg->deserialize(na_json);
   #endif
#else
   ReferenceAggregate ra;
   BaseAggregate *agg = &ra;
   agg->deserialize(ra_json);
#endif

   cout << "--------------- Serialize it now:" << endl;
   StringBuffer sb;
   PrettyWriter<StringBuffer> writer(sb);

   agg->serialize(&writer);
   cout << "Serialized: \n" << sb.GetString() << endl;
}

static void runSerialize( void )
{
   StringBuffer sb;
   PrettyWriter<StringBuffer> writer(sb);

#if NA_TEST
   #if TPE_TEST
      TPEPredictUserDataAggregate tpe;
      tpe.serialize(&writer);
   #else
      NestedWithReferenceAggregate na;
      na.enumField.value(Bct::Workflow::Implementation::ReferenceEnum::Poor);
      na.serialize( &writer );
   #endif
#else
   ReferenceAggregate ra;
   ra.enumField.value(Bct::Workflow::Implementation::ReferenceEnum::Poor);
   std::vector<int32_t> vectorInt;
   vectorInt.push_back( -1 );
   vectorInt.push_back( 3 );
   vectorInt.push_back( 5 );
   ra.vectorIntField.value( vectorInt );
   ra.serialize( &writer );
#endif

   cout << "Serialized: \n" << sb.GetString() << endl;
}

int main(int argc, char** argv)
{
   parseArgs( argc, argv);
   cout << "bSerialize: " << bSerialize << "\n------------------------" << endl;

   if( bSerialize )
   {
      runSerialize();
   }
   else{
      runDeserialize();
   }

   //----------------
   return 0;
}

// EOF
