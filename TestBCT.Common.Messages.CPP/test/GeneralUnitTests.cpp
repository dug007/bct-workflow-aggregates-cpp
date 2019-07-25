#include "Sample1Aggregate.h"
#include "BaseAggregate.h"
#include "BaseField.h"

#include "AbstractField.h"
#include "AbstractAggregate.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace Bct::Workflow::Aggregates;


TEST_CASE("General", "[test]")
{
   // General unit tests ----------------------------------------------
   Sample1Aggregate a;
   CHECK(a.Field1.State() == FieldStateEnum::FieldState::NotSet);
   CHECK(a.Field7.State() == FieldStateEnum::FieldState::NotSet);
   CHECK(a.Field7d.State() == FieldStateEnum::FieldState::Default);
   CHECK(a.Field7c.State() == FieldStateEnum::FieldState::Constant);
   CHECK(a.Field1.FieldSetCounter() == 0);
   a.Field1 = 2.0;
   a.Field7 = 3;          // via assignment operator
   a.Field7d.Value(4);    // via function
   CHECK(a.Field7d.FieldSetCounter() == 3);
   double f1 = a.Field1;  // via conversion operator
   //a.Field7ro = 3;      //cannot compile - no assignment operator
   //a.Field7ro.Value(3); //connot compile - setter is private
   CHECK_THROWS_AS(a.Field7c = 3, char*);  // throws on assignment
   CHECK_THROWS_AS(a.Field7c.Value(3), char*);  // throws on set
   CHECK(f1 == 2.0);
   CHECK(a.Field1.State() == FieldStateEnum::FieldState::Set);
   CHECK(a.Field7.Value() == 3);
   CHECK((int32_t)a.Field7 == 3);
   CHECK(a.Field7ro.Value() == 5);  // readable but not writeable
   CHECK((int32_t)a.Field7ro == 5); // readable but not writeable
   CHECK(a.Field7ro.State() == FieldStateEnum::FieldState::Constant);
   CHECK(a.Field7c.Value() == 6);  // readable but not writeable
   CHECK((int32_t)a.Field7c == 6); // readable but not writeable
   CHECK(a.Field7c.State() == FieldStateEnum::FieldState::Constant);
   CHECK(a.Field7.State() == FieldStateEnum::FieldState::Set);
   CHECK(a.Field7d.Value() == 4);
   CHECK((int32_t)a.Field7d == 4);
   CHECK(a.Field7d.State() == FieldStateEnum::FieldState::Set);

   // set back to default
   a.Field7d = -1;
   CHECK(a.Field7d.Value() == -1);
   CHECK(a.Field7d.State() == FieldStateEnum::FieldState::Default);

   a.UpdateCalculatedFields();
   CHECK(a.Field1.Value() == 22.0);

   // Testing $EnteredLater
   a.Field7x = 98;
   a.Field7d = 99;
   a.UpdateCalculatedFields();    // "Field7d Field7x $EnteredLater", "Field7d")
   CHECK(a.Field7.Value() == a.Field7d.Value());
   a.Field7x = a.Field7x.Value();
   a.UpdateCalculatedFields();    // "Field7x Field7d $EnteredLater", "Field7x")
   CHECK(a.Field7.Value() == a.Field7x.Value());

   // Testing Enum fields
   CHECK(a.FieldEnum.Value() == FieldStateEnum::NotSet);
   a.FieldEnum.Value(FieldStateEnum::Set);
   a.FieldEnum = FieldStateEnum::Default;
      CHECK(a.FieldEnum.Value() == FieldStateEnum::Default);

   CHECK(a.FieldEnumRo.State() == FieldStateEnum::Unavailable);
   //   a.FieldEnumRo.Value(FieldStateEnum::Set);
   //   a.FieldEnumRo = FieldStateEnum::Default;
}
