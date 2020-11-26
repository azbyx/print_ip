#define NDEBUG

//#include <gtest/gtest.h>
//#include "headers/generators_ip.h"
//#include "headers/print_ip.h"

/*
TEST(Traversing_a_container_with_its_own_iterator, by_simple_for) {

    // Arrange

    // Act

    // Assert
    ASSERT_EQ(size_arr, size_list);

}

TEST(Traversing_a_container_with_its_own_iterator, by_range_for) {

    // Arrange
    LList_ext_realoc<size_t> custom_list;
    const size_t size_arr{5};
    size_t data[] = {1, 1, 2, 3, 5, 8, 13};
    size_t size_list{0};

    // Act
    for (size_t i = 0; i < size_arr; i++){
            custom_list.Add(data[i]);
    }
    for ([[maybe_unused]]const auto& it : custom_list){
            ++size_list;
    }

    // Assert
    ASSERT_EQ(size_arr, size_list);

}

TEST(Filling_container_using_the_Add_method, with_lvalue) {

    // Arrange
    LList_ext_realoc<bunch<size_t>> custom_list_lv;
    LList_ext_realoc<bunch<size_t>>::size_type size_list_lv{0},
                                               requires_size{SZ + 5};

    // Act
    for (size_t i = 0; i < requires_size; i++){
            bunch<size_t> fct{i, MyFactorial(i)};
            custom_list_lv.Add(fct);
    }
    for (auto it = custom_list_lv.begin(); it != custom_list_lv.end(); ++it){
            ++size_list_lv;
    }

    // Assert
    ASSERT_EQ(requires_size, size_list_lv);

}

TEST(Filling_container_using_the_Add_method, with_rvalue) {

    // Arrange
    LList_ext_realoc<bunch<size_t>> custom_list_rv;
    LList_ext_realoc<bunch<size_t>>::size_type size_list_rv{0},
                                               requires_size{SZ + 5};

    // Act
    for (size_t  i = 0; i < requires_size; i++){
            custom_list_rv.Add(bunch<size_t>{i, MyFactorial(i)});
    }
    for (auto it = custom_list_rv.begin(); it != custom_list_rv.end(); ++it){
            ++size_list_rv;
    }

    // Assert
    ASSERT_EQ(requires_size, size_list_rv);

}

TEST(Filling_container_using_the_Emplace_method, by_value) {

    // Arrange
    LList_ext_realoc<bunch<size_t>> custom_list_rv;
    LList_ext_realoc<bunch<size_t>>::size_type size_list_rv{0},
                                               requires_size{SZ + 5};

    // Act
    for (size_t  i = 0; i < requires_size; i++){
            custom_list_rv.Emplace(i, MyFactorial(i));
    }
    for (auto it = custom_list_rv.begin(); it != custom_list_rv.end(); ++it){
            ++size_list_rv;
    }

    // Assert
    ASSERT_EQ(requires_size, size_list_rv);

}

int main(int argc, char** argv) {

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}
*/
