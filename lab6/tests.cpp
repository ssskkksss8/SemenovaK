#include <gtest/gtest.h>
#include "npc.hpp"
#include "orc.hpp"
#include "druids.hpp"
#include "squirrel.hpp"
#include "fighting.hpp"

TEST(NPCInteractions, test1) {
    std::shared_ptr<NPC> druids = std::make_shared<druids>(0, 0);
    std::shared_ptr<NPC> squirrel = std::make_shared<squirrel>(1, 1);

    bool murder = druids->accept(squirrel);
    ASSERT_FALSE(murder);
}

TEST(NPCInteractions, test2) {
    std::shared_ptr<NPC> druids = std::make_shared<druids>(0, 0);
    std::shared_ptr<NPC> orc = std::make_shared<orc>(1, 1);

    bool murder = druids->accept(orc);
    ASSERT_TRUE(murder);
}

TEST(NPCInteractions, test3) {
    std::shared_ptr<NPC> druids1 = std::make_shared<druids>(0, 0);
    std::shared_ptr<NPC> druids2 = std::make_shared<druids>(1, 1);

    bool murder = druids1->accept(druids2);
    ASSERT_FALSE(murder);
}

TEST(NPCInteractions, test4) {
    std::shared_ptr<NPC> squirrel1 = std::make_shared<squirrel>(0, 0);
    std::shared_ptr<NPC> squirrel2 = std::make_shared<squirrel>(1, 1);

    bool murder = squirrel1->accept(squirrel2);
    ASSERT_FALSE(murder);
}

TEST(NPCInteractions, test5) {
    std::shared_ptr<NPC> squirrel = std::make_shared<squirrel>(0, 0);
    std::shared_ptr<NPC> orc = std::make_shared<orc>(1, 1);

    bool murder = squirrel->accept(orc);
    ASSERT_TRUE(murder);
}

TEST(NPCInteractions, test6) {
    std::shared_ptr<NPC> squirrel = std::make_shared<squirrel>(0, 0);
    std::shared_ptr<NPC> druids = std::make_shared<druids>(1, 1);

    bool murder = squirrel->accept(druids);
    ASSERT_TRUE(murder);
}

TEST(NPCInteractions, test7) {
    std::shared_ptr<NPC> orc = std::make_shared<orc>(0, 0);
    std::shared_ptr<NPC> squirrel = std::make_shared<squirrel>(1, 1);

    bool murder = orc->accept(squirrel);
    ASSERT_FALSE(murder);
}

TEST(NPCInteractions, test8) {
    std::shared_ptr<NPC> orc1 = std::make_shared<orc>(0, 0);
    std::shared_ptr<NPC> orc2 = std::make_shared<orc>(1, 1);

    bool murder = orc1->accept(orc2);
    ASSERT_FALSE(murder);
}

TEST(NPCInteractions, test9) {
    std::shared_ptr<NPC> orc = std::make_shared<orc>(0, 0);
    std::shared_ptr<NPC> druids = std::make_shared<druids>(1, 1);

    bool murder = orc->accept(druids);
    ASSERT_FALSE(murder);
}

TEST(ObserverTests, test) {
    std::shared_ptr<NPC> orc = std::make_shared<orc>(0, 0);
    std::shared_ptr<NPC> druids = std::make_shared<druids>(1, 1);
    
    druids->subscribe(TextObserver::get());
    testing::internal::CaptureStdout();
    orc->accept(druids);
    std::string output = testing::internal::GetCapturedStdout();
    
    testing::internal::CaptureStdout();
    std::cout << std::endl << "Murder --------" << std::endl <<  "druids: { x:1, y:1} " << std::endl
              << "orc: { x:0, y:0} " << std::endl;
    std::string answer = testing::internal::GetCapturedStdout();
    
    ASSERT_TRUE(output == answer);
}

int main(int argc, char** argv){

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
