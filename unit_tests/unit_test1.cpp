#include "../src/executable.cpp"
#include "gtest/gtest.h"

#pragma region test_cmd
//------------------------------------------------START OF TEST_CMD TESTS-----------------------------------------------

TEST(TestClass, noFlagFile){
    char * args[] = {(char *)"test", (char *)"unit_tests/unit_test1.cpp", (char *)NULL}; 
    Executable* t = new Executable("test", args, 3); 
    EXPECT_EQ(t->execute(), true); 
    
}


TEST(TestClass, eFlagFile){
    char * args[] = {(char *)"test", (char *)"-e", (char *)"unit_tests/unit_test1.cpp", (char *)NULL}; 
    Executable* t = new Executable("test", args, 4); 
    EXPECT_EQ(t->execute(), true); 

}


TEST(TestClass, eFlagblah){
    char * args[] = {(char *)"test", (char *)"-e", (char *)"yooooo", (char *)NULL}; 
    Executable* t = new Executable("test", args, 3); 
    EXPECT_EQ(t->execute(), false); 

}

TEST(TestClass, fFlagFile){
    char * args[] = {(char *)"test", (char *)"-f", (char *)"unit_tests/unit_test1.cpp", (char *)NULL}; 
    Executable* t = new Executable("test", args, 4); 
    EXPECT_EQ(t->execute(), true);
    
}

TEST(TestClass, dFlagFile){
    char * args[] = {(char *)"test", (char *)"-d", (char *)"unit_tests/unit_test1.cpp", (char *)NULL}; 
    Executable* t = new Executable("test", args, 4); 
    EXPECT_EQ(t->execute(), false); 
}

TEST(TestClass, dFlagFolder){
    char * args[] = {(char *)"test", (char *)"-d", (char *)"header/", (char *)NULL}; 
    Executable* t = new Executable("test", args, 4); 
    EXPECT_EQ(t->execute(), true); 
}


TEST(TestClass, noFlagDirectory){
    char * args[] = {(char *)"test", (char *)"unit_tests", (char *)NULL}; 
    Executable* t = new Executable("test", args, 3); 
    EXPECT_EQ(t->execute(), true); 
}


TEST(TestClass, eFlagDirectory){
    char * args[] = {(char *)"test", (char *)"-e", (char *)"unit_tests", (char *)NULL}; 
    Executable* t = new Executable("test", args, 4); 
    EXPECT_EQ(t->execute(), true); 

}

TEST(TestClass, fFlagDirectory){
    char * args[] = {(char *)"test", (char *)"-f", (char *)"~/cs100/assns/spring-2019-assignment-cs100-dance-team/unit_tests", (char *)NULL}; 
    Executable* t = new Executable("test", args, 4); 
    EXPECT_EQ(t->execute(), false); 
    
}

TEST(TestClass, dFlagDirectory){
    char * args[] = {(char *)"test", (char *)"-d", (char *)"unit_tests", (char *)NULL}; 
    Executable* t = new Executable("test", args, 4); 
    EXPECT_EQ(t->execute(), true); 
    
}

#pragma endregion
//--------------------------------------------------END OF TEST_CMD TESTS--------------------------------------------
//
//------------------------------------------------START OF EXECVP TESTS-----------------------------------------------
#pragma region execvp


TEST(ExecutableTest, ValidCommandAndArg){
    
    char * argList[] = {(char *)"ls", (char *)"-a", (char *)NULL}; 

    Executable * exec = new Executable("ls", argList, 3); 

    EXPECT_EQ(exec->execute(), true); 
}

TEST(ExecutableTest, invalidCommandAndArg){

    char * argList[] = {(char *)"dddd", (char *)"dddd", (char *)NULL};

    Executable * exec = new Executable("dddd", argList, 3);

    EXPECT_EQ(exec->execute(), false);
}


TEST(ExecutableTest, invalidCommandValidArg){

    char * argList[] = {(char *)"ls", (char *)"-a", (char *)NULL};

    Executable * exec = new Executable("dddd", argList, 3);

    EXPECT_EQ(exec->execute(), false);
}


TEST(ExecutableTest, validCommandInvalidArg){

    char * argList[] = {(char *)"dddd", (char *)"dddd", (char *)NULL};

    Executable * exec = new Executable("ls", argList, 3);

    EXPECT_EQ(exec->execute(), false);
}

TEST(ExecutableTest, emptyCommandAndValidArg){

    char * argList[] = {(char *)"ls", (char *)"-a", (char *)NULL};

    Executable * exec = new Executable("", argList, 3);

    EXPECT_EQ(exec->execute(), false);
}

#pragma endregion
//------------------------------------------------END OF EXECVP TESTS-----------------------------------------------
//
//------------------------------------------------MAIN DRIVER PROGRAM-----------------------------------------------
#pragma region main

int main(int argc, char **argv) { 
     ::testing::InitGoogleTest(&argc, argv);
     return RUN_ALL_TESTS(); 
}
#pragma endregion
//------------------------------------------------END OF ALL TESTS---------------------------------------------------