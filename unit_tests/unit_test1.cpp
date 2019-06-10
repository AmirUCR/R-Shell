#include "../src/executable.cpp"
#include "../src/input_redirector.cpp"
#include "../src/and.cpp"
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

    delete exec;
}

TEST(ExecutableTest, invalidCommandAndArg){

    char * argList[] = {(char *)"dddd", (char *)"dddd", (char *)NULL};

    Executable * exec = new Executable("dddd", argList, 3);

    EXPECT_EQ(exec->execute(), false);

    delete exec;
}


TEST(ExecutableTest, invalidCommandValidArg){

    char * argList[] = {(char *)"ls", (char *)"-a", (char *)NULL};

    Executable * exec = new Executable("dddd", argList, 3);

    EXPECT_EQ(exec->execute(), false);

    delete exec;
}


TEST(ExecutableTest, validCommandInvalidArg){

    char * argList[] = {(char *)"dddd", (char *)"dddd", (char *)NULL};

    Executable * exec = new Executable("ls", argList, 3);

    EXPECT_EQ(exec->execute(), true);

    delete exec;
}

TEST(ExecutableTest, emptyCommandAndValidArg){

    char * argList[] = {(char *)"ls", (char *)"-a", (char *)NULL};

    Executable * exec = new Executable("", argList, 3);

    EXPECT_EQ(exec->execute(), false);

    delete exec;
}

#pragma endregion
//------------------------------------------------END OF EXECVP TESTS-----------------------------------------------
//
//------------------------------------------------START OF INPUT REDIRECTION TESTS-----------------------------------------------

// Testing: cat < text.txt
TEST(Inputredirection_Tests, Valid_Input_File_Test){
    
    char * argList1[] = {(char *)"cat", (char *)NULL}; 
    char * argList2[] = {(char *)"text.txt", (char *)NULL};

    Executable * exec1 = new Executable((char *)"cat", argList1, 2);
    Executable * exec2 = new Executable((char *)"text.txt", argList2, 2);

    InputRedirector* ir = new InputRedirector();
    ir->SetLeft(exec1);
    ir->SetRight(exec2);
    
    EXPECT_EQ(ir->execute(0 , 1), true);

    delete ir;
    delete exec2;
    delete exec1;
}

// Testing: cat < invalidFile.txt
TEST(Inputredirection_Tests, Invalid_Input_File_Test){
    
    char * argList1[] = {(char *)"cat", (char *)NULL}; 
    char * argList2[] = {(char *)"invalidFile.txt", (char *)NULL};

    Executable * exec1 = new Executable((char *)"cat", argList1, 2);
    Executable * exec2 = new Executable((char *)"invalidFile.txt", argList2, 2);

    InputRedirector* ir = new InputRedirector();
    ir->SetLeft(exec1);
    ir->SetRight(exec2);
    
    EXPECT_EQ(ir->execute(0 , 1), false);

    delete ir;
    delete exec2;
    delete exec1;
}

TEST(Inputredirection_Tests, Valid_Input_File_Composite_Test){
    
    char * argList1[] = {(char *)"cat", (char *)NULL}; 
    char * argList2[] = {(char *)"text.txt", (char *)NULL};

    Executable* exec1 = new Executable((char *)"cat", argList1, 2);
    Executable* exec2 = new Executable((char *)"text.txt", argList2, 2);

    InputRedirector* ir = new InputRedirector();
    ir->SetLeft(exec1);
    ir->SetRight(exec2);

    char * argList3[] = {(char *)"ls", (char *)NULL};

    Executable* exec3 = new Executable((char *)"ls", argList3, 2);

    And* a = new And();
    a->SetLeft(ir);
    a->SetRight(exec3);
    
    EXPECT_EQ(a->execute(0 , 1), true);

    delete a;
    delete ir;
    delete exec2;
    delete exec3;
    delete exec1;
}

//------------------------------------------------MAIN DRIVER PROGRAM-----------------------------------------------
#pragma region main

int main(int argc, char **argv) { 
     ::testing::InitGoogleTest(&argc, argv);
     return RUN_ALL_TESTS(); 
}
#pragma endregion
//------------------------------------------------END OF ALL TESTS---------------------------------------------------