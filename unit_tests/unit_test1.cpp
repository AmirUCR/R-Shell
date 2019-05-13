#include "../header/executable.h"

#include "gtest/gtest.h"


TEST(ExecutableTest, ValidCommandAndArg){
    
    char * argList[] = {"ls", "-a", NULL}; 

    Executable * exec = new Executable("ls", argList); 

    EXPECT_EQ(exec->execute(), true); 
}


TEST(ExecutableTest, invalidCommandAndArg){

    char * argList[] = {"dddd", "dddd", NULL};

    Executable * exec = new Executable("dddd", argList);

    EXPECT_EQ(exec->execute(), false);
}


TEST(ExecutableTest, invalidCommandValidArg){

    char * argList[] = {"ls", "-a", NULL};

    Executable * exec = new Executable("dddd", argList);

    EXPECT_EQ(exec->execute(), false);
}


TEST(ExecutableTest, validCommandInvalidArg){

    char * argList[] = {"dddd", "dddd", NULL};

    Executable * exec = new Executable("ls", argList);

    EXPECT_EQ(exec->execute(), false);
}

TEST(ExecutableTest, emptyCommandAndValidArg){

    char * argList[] = {"ls", "-a", NULL};

    Executable * exec = new Executable("", argList);

    EXPECT_EQ(exec->execute(), false);
}

TEST(ExecutableTest, validCommandAndEmptyArg){

    char * argList[] = {NULL};

    Executable * exec = new Executable("ls", argList);

    EXPECT_EQ(exec->execute(), false);
}

int main(int argc, char **argv) { 
     ::testing::InitGoogleTest(&argc, argv);
     return RUN_ALL_TESTS(); 
}