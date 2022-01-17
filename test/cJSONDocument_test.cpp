#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "unity.h"

#include "bstd/cJSONDocument.h"


static const char *jbasic = R"( { "isnull": null, "istrue": true, "isfalse": false, "ispos": 10, "isneg": -3, "isreal": 3.1415, "isstr": "foobar" } )";
static const char *jnested = R"( { "first": { "second": { "foobar": true } } } )";
static const char *jarray = R"( { "foobar": [ 3, 14, 15 ] } )";
static const char *jobjarray = R"( { "foobar": [ { "value": 3 }, { "value": 14 }, { "value": 15 } ] } )";


void test_cJSONDocument_parse()
{
    bstd::cJSONDocument j;

    TEST_ASSERT_TRUE( j.parse( jbasic ) );
    TEST_ASSERT_TRUE( j );
}


void test_cJSONDocument_values()
{
    bstd::cJSONDocument j( jbasic );

    TEST_ASSERT_TRUE( j["isnull"].is_null() );

    TEST_ASSERT_TRUE( j["istrue"].get( false ) );
    TEST_ASSERT_FALSE( j["isfalse"].get( true ) );

    TEST_ASSERT_EQUAL_INT( 10, j["ispos"].get( 0 ) );
    TEST_ASSERT_EQUAL_INT( -3, j["isneg"].get( 0 ) );

    TEST_ASSERT_EQUAL_FLOAT( 3.1415, j["isreal"].get( 0.0 ) );

    TEST_ASSERT_EQUAL_STRING( "foobar", j["isstr"].get( "" ) );
}


void test_cJSONDocument_objects()
{
    bstd::cJSONDocument j( jnested );

    TEST_ASSERT_TRUE( j["first"] );
    TEST_ASSERT_TRUE( j["first"]["second"] );
    TEST_ASSERT_TRUE( j["first"]["second"]["foobar"].get( false ) );
}


void test_cJSONDocument_array()
{
    bstd::cJSONDocument j( jarray );

    TEST_ASSERT_TRUE( j["foobar"].is_array() );
    TEST_ASSERT_EQUAL_INT( 3, j["foobar"].size() );

    size_t n = 0;
    TEST_ASSERT_EQUAL_INT( 3, j["foobar"][n++].get( 0 ) );
    TEST_ASSERT_EQUAL_INT( 14, j["foobar"][n++].get( 0 ) );
    TEST_ASSERT_EQUAL_INT( 15, j["foobar"][n++].get( 0 ) );
    TEST_ASSERT_EQUAL_INT( -1, j["foobar"][n++].get( -1 ) );
}


void test_cJSONDocument_objarray()
{
    const bstd::cJSONDocument j( jobjarray );

    TEST_ASSERT_TRUE( j["foobar"].is_array() );
    TEST_ASSERT_EQUAL_INT( 3, j["foobar"].size() );

    size_t n = 0;
    TEST_ASSERT_EQUAL_INT( 3, j["foobar"][n++]["value"].get( 0 ) );
    TEST_ASSERT_EQUAL_INT( 14, j["foobar"][n++]["value"].get( 0 ) );
    TEST_ASSERT_EQUAL_INT( 15, j["foobar"][n++]["value"].get( 0 ) );
}


extern "C" void app_main()
{
    vTaskDelay( 3000 / portTICK_PERIOD_MS );
    UNITY_BEGIN();

    RUN_TEST( test_cJSONDocument_parse );
    RUN_TEST( test_cJSONDocument_values );
    RUN_TEST( test_cJSONDocument_objects );
    RUN_TEST( test_cJSONDocument_array );
    RUN_TEST( test_cJSONDocument_objarray );

    UNITY_END();
}
