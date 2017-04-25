#include "gtest/gtest.h"

extern "C" {
#include "iri_adapter.h"
}

namespace {
    class IriModelTest : public ::testing::Test
    {
    protected:
        void SetUp()
        {
        }

        void TearDown()
        {
        }
    };

    TEST_F( IriModelTest, standartTest)
    {
        MODEL_PARMS iriModelParms;
        iriModelParms.lati = 50.0;
        iriModelParms.longi = 40.0;
        iriModelParms.height = 100.0;
        iriModelParms.year = 2000;
        iriModelParms.mmdd = 101;
        iriModelParms.dhour = 1.5;
        iriModelParms.independentVar = HOUR;
        iriModelParms.beginRange = 0.0;
        iriModelParms.endRange = 24.0;
        iriModelParms.stepRange = 0.5;
        iriModelParms.h_tec_max = 1000.0;

        call_iri(&iriModelParms);
        std::vector<STANDART_RESULT> resultData;
        parse_model_ouput(&iriModelParms, &resultData);
        EXPECT_EQ(48, resultData.size());
        EXPECT_EQ(4, resultData[8].dhour);
        ASSERT_LT(5.5555, resultData[8].tec);
        ASSERT_GT(5.6, resultData[8].tec);
        EXPECT_EQ(3726, resultData[8].nE);

    }
}
