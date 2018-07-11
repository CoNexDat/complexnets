//
// Created by María de los Ángeles Arlanti on 01/07/18.
// Modified by ... on ../../..
//
#include <gtest/gtest.h>
#include "ConnectivityVerifier.h"


namespace connectivityVerifierTest
{

    using namespace graphpp;
    using namespace std;
    using ::testing::Test;

    class ConnectivityVerifierTestFixture : public Test
    {

    public:

        ConnectivityVerifier<Graph, Vertex> connectivityVerifier;

        ConnectivityVerifierTestFixture(){
            //connectivityVerifier = new ConnectivityVerifier;
        }

        virtual ~ConnectivityVerifierTestFixture(){
            //delete connectivityVerifier;
        }


        virtual void SetUp()
        {

        }

        virtual void TearDown()
        {

        }

    };

    TEST_F(ConnectivityVerifierTestFixture, VertexVisitedTest){
        connectivityVerifier.vertexesInComponent.clear();

        connectivityVerifier.vertexesLeft.push_back(0);
        connectivityVerifier.vertexesLeft.push_back(1);
        connectivityVerifier.vertexesLeft.push_back(2);
        connectivityVerifier.vertexesLeft.push_back(3);

        ASSERT_EQ(0, connectivityVerifier.vertexesInComponent.size());
        ASSERT_EQ(4, connectivityVerifier.vertexesLeft.size());

        connectivityVerifier.visited(0);

        ASSERT_EQ(1, connectivityVerifier.vertexesInComponent.size());
        ASSERT_EQ(3, connectivityVerifier.vertexesLeft.size());
    }
}

