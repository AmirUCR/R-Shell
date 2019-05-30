#include "../src/executable.cpp"
#include "gtest/gtest.h"

#pragma region test_cmd
//------------------------------------------------START OF TEST_CMD TESTS-----------------------------------------------

TEST(TestClass, noFlagFile){
    char * args[] = {"test", "unit_tests/unit_test1.cpp", NULL}; 
    Executable* t = new Executable("test", args, 3); 
    EXPECT_EQ(t->execute(), true); 
    
}


TEST(TestClass, eFlagFile){
    char * args[] = {"test", "-e", "unit_tests/unit_test1.cpp", NULL}; 
    Executable* t = new Executable("test", args, 4); 
    EXPECT_EQ(t->execute(), true); 

}


TEST(TestClass, eFlagblah){
    char * args[] = {"test", "-e", "yooooo", NULL}; 
    Executable* t = new Executable("test", args, 3); 
    EXPECT_EQ(t->execute(), false); 

}

TEST(TestClass, fFlagFile){
    char * args[] = {"test", "-f", "unit_tests/unit_test1.cpp", NULL}; 
    Executable* t = new Executable("test", args, 4); 
    EXPECT_EQ(t->execute(), true);
    
}

TEST(TestClass, dFlagFile){
    char * args[] = {"test", "-d", "unit_tests/unit_test1.cpp", NULL}; 
    Executable* t = new Executable("test", args, 4); 
    EXPECT_EQ(t->execute(), false); 
}

TEST(TestClass, dFlagFolder){
    char * args[] = {"test", "-d", "header/", NULL}; 
    Executable* t = new Executable("test", args, 4); 
    EXPECT_EQ(t->execute(), true); 
}


TEST(TestClass, noFlagDirectory){
    char * args[] = {"test", "unit_tests", NULL}; 
    Executable* t = new Executable("test", args, 3); 
    EXPECT_EQ(t->execute(), true); 
}


TEST(TestClass, eFlagDirectory){
    char * args[] = {"test", "-e", "unit_tests", NULL}; 
    Executable* t = new Executable("test", args, 4); 
    EXPECT_EQ(t->execute(), true); 

}

TEST(TestClass, fFlagDirectory){
    char * args[] = {"test", "-f", "~/cs100/assns/spring-2019-assignment-cs100-dance-team/unit_tests", NULL}; 
    Executable* t = new Executable("test", args, 4); 
    EXPECT_EQ(t->execute(), false); 
    
}

TEST(TestClass, dFlagDirectory){
    char * args[] = {"test", "-d", "unit_tests", NULL}; 
    Executable* t = new Executable("test", args, 4); 
    EXPECT_EQ(t->execute(), true); 
    
}

#pragma endregion
//--------------------------------------------------END OF TEST_CMD TESTS--------------------------------------------
//
//------------------------------------------------START OF EXECVP TESTS-----------------------------------------------
#pragma region execvp


TEST(ExecutableTest, ValidCommandAndArg){
    
    char * argList[] = {"ls", "-a", NULL}; 

    Executable * exec = new Executable("ls", argList, 3); 

    EXPECT_EQ(exec->execute(), true); 
}

TEST(ExecutableTest, invalidCommandAndArg){

    char * argList[] = {"dddd", "dddd", NULL};

    Executable * exec = new Executable("dddd", argList, 3);

    EXPECT_EQ(exec->execute(), false);
}


TEST(ExecutableTest, invalidCommandValidArg){

    char * argList[] = {"ls", "-a", NULL};

    Executable * exec = new Executable("dddd", argList, 3);

    EXPECT_EQ(exec->execute(), false);
}


TEST(ExecutableTest, validCommandInvalidArg){

    char * argList[] = {"dddd", "dddd", NULL};

    Executable * exec = new Executable("ls", argList, 3);

    EXPECT_EQ(exec->execute(), false);
}

TEST(ExecutableTest, emptyCommandAndValidArg){

    char * argList[] = {"ls", "-a", NULL};

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