#include "gtest/gtest.h"
#include "helper_for_tests.h"
#include "source/calculation/game_state_controller.h"
#include "source/calculation/move_generator.h"

using namespace blaengine::calculation;

TEST(MoveGenerator, test_expectedMovesInMoves1) {
  vector<Move> moves = {{10, 0, Piece::white_pawn},
                        {0, 0, Piece::black_king},
                        {0, 1, Piece::left_piece}};
  vector<Move> expected_moves = {{0, 0, Piece::black_king},
                                 {0, 1, Piece::left_piece},
                                 {10, 0, Piece::white_pawn}};

  ASSERT_TRUE(expectedMovesInMoves(moves, expected_moves));
}

TEST(MoveGenerator, test_expectedMovesInMoves2) {
  vector<Move> moves = {{10, 0, Piece::white_pawn}, {0, 1, Piece::left_piece}};
  vector<Move> expected_moves = {{0, 0, Piece::black_king},
                                 {0, 1, Piece::left_piece},
                                 {10, 0, Piece::white_pawn}};

  ASSERT_FALSE(expectedMovesInMoves(moves, expected_moves));
}

TEST(MoveGenerator, test_expectedMovesInMoves3) {
  vector<Move> moves = {{10, 0, Piece::white_pawn},
                        {0, 0, Piece::black_king},
                        {0, 1, Piece::left_piece}};
  vector<Move> expected_moves = {{0, 0, Piece::black_king},
                                 {10, 0, Piece::white_pawn}};

  ASSERT_TRUE(expectedMovesInMoves(moves, expected_moves));
}

TEST(MoveGenerator, test_expectedMovesInMoves4) {
  vector<Move> moves = {{10, 0, Piece::white_pawn},
                        {0, 0, Piece::black_king},
                        {0, 1, Piece::left_piece}};
  vector<Move> expected_moves = {{0, 0, Piece::black_king},
                                 {21, 63, Piece::white_pawn}};

  ASSERT_FALSE(expectedMovesInMoves(moves, expected_moves));
}

// ----------------------- white pawn tests ------------------------------------

TEST(MoveGenerator, test_w_pawn_moves_ground_free) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 10;
  game_state.board.fields[field_before] = Piece::white_pawn;

  auto pawn_moves = move_generator.getPawnMoves(game_state, field_before);
  vector<Move> expected_moves = {{field_before, 18, Piece::left_piece},
                                 {field_before, 26, Piece::left_piece}};

  ASSERT_TRUE(expectedMovesInMoves(pawn_moves, expected_moves));
}

TEST(MoveGenerator, test_w_pawn_moves_ground_blocked) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 10;
  game_state.board.fields[field_before] = Piece::white_pawn;
  game_state.board.fields[18] = Piece::white_pawn;

  auto pawn_moves = move_generator.getPawnMoves(game_state, field_before);
  vector<Move> expected_moves = {};

  ASSERT_TRUE(expectedMovesInMoves(pawn_moves, expected_moves));
}

TEST(MoveGenerator, test_w_pawn_moves_ground_blocked_one) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 10;
  game_state.board.fields[field_before] = Piece::white_pawn;
  game_state.board.fields[26] = Piece::white_pawn;

  auto pawn_moves = move_generator.getPawnMoves(game_state, field_before);
  vector<Move> expected_moves = {{field_before, 18, Piece::left_piece}};

  ASSERT_TRUE(expectedMovesInMoves(pawn_moves, expected_moves));
}

TEST(MoveGenerator, test_w_pawn_moves_ground_free_take_two) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 10;
  game_state.board.fields[field_before] = Piece::white_pawn;
  game_state.board.fields[19] = Piece::black_queen;
  game_state.board.fields[17] = Piece::black_queen;

  auto pawn_moves = move_generator.getPawnMoves(game_state, field_before);
  vector<Move> expected_moves = {{field_before, 18, Piece::left_piece},
                                 {field_before, 26, Piece::left_piece},
                                 {field_before, 19, Piece::left_piece},
                                 {field_before, 17, Piece::left_piece}};

  ASSERT_TRUE(expectedMovesInMoves(pawn_moves, expected_moves));
}

TEST(MoveGenerator, test_w_pawn_moves_mid_free_not_take) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 18;
  game_state.board.fields[field_before] = Piece::white_pawn;
  game_state.board.fields[27] = Piece::white_king;
  game_state.board.fields[25] = Piece::white_pawn;

  auto pawn_moves = move_generator.getPawnMoves(game_state, field_before);
  vector<Move> expected_moves = {{field_before, 26, Piece::left_piece}};

  ASSERT_TRUE(expectedMovesInMoves(pawn_moves, expected_moves));
}

TEST(MoveGenerator, test_w_pawn_moves_border_free_take_right) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 16;
  game_state.board.fields[field_before] = Piece::white_pawn;
  game_state.board.fields[25] = Piece::black_queen;
  game_state.board.fields[23] = Piece::black_queen;
  game_state.board.fields[31] = Piece::black_queen;
  game_state.board.fields[30] = Piece::black_queen;
  game_state.board.fields[15] = Piece::black_queen;

  auto pawn_moves = move_generator.getPawnMoves(game_state, field_before);
  vector<Move> expected_moves = {{field_before, 24, Piece::left_piece},
                                 {field_before, 25, Piece::left_piece}};

  ASSERT_TRUE(expectedMovesInMoves(pawn_moves, expected_moves));
}

TEST(MoveGenerator, test_w_pawn_moves_border_free_take_left) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 23;
  game_state.board.fields[field_before] = Piece::white_pawn;
  game_state.board.fields[30] = Piece::black_queen;
  game_state.board.fields[32] = Piece::black_queen;
  game_state.board.fields[24] = Piece::black_queen;
  game_state.board.fields[16] = Piece::black_queen;
  game_state.board.fields[8] = Piece::black_queen;

  auto pawn_moves = move_generator.getPawnMoves(game_state, field_before);
  vector<Move> expected_moves = {{field_before, 31, Piece::left_piece},
                                 {field_before, 30, Piece::left_piece}};

  ASSERT_TRUE(expectedMovesInMoves(pawn_moves, expected_moves));
}

TEST(MoveGenerator, test_w_pawn_moves_promotion) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 48;
  game_state.board.fields[field_before] = Piece::white_pawn;
  game_state.board.fields[57] = Piece::black_queen;
  game_state.board.fields[63] = Piece::black_queen;

  auto pawn_moves = move_generator.getPawnMoves(game_state, field_before);
  vector<Move> expected_moves = {{field_before, 56, Piece::white_bishop},
                                 {field_before, 56, Piece::white_knight},
                                 {field_before, 56, Piece::white_queen},
                                 {field_before, 56, Piece::white_rook},
                                 {field_before, 57, Piece::white_bishop},
                                 {field_before, 57, Piece::white_knight},
                                 {field_before, 57, Piece::white_queen},
                                 {field_before, 57, Piece::white_rook}};

  ASSERT_TRUE(expectedMovesInMoves(pawn_moves, expected_moves));
}

// ----------------------- black pawn tests ------------------------------------

TEST(MoveGenerator, test_b_pawn_moves_ground_free) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 51;
  game_state.board.fields[field_before] = Piece::black_pawn;

  auto pawn_moves = move_generator.getPawnMoves(game_state, field_before);
  vector<Move> expected_moves = {{field_before, 43, Piece::left_piece},
                                 {field_before, 35, Piece::left_piece}};

  ASSERT_TRUE(expectedMovesInMoves(pawn_moves, expected_moves));
}

TEST(MoveGenerator, test_b_pawn_moves_ground_blocked) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 52;
  game_state.board.fields[field_before] = Piece::black_pawn;
  game_state.board.fields[44] = Piece::white_pawn;

  auto pawn_moves = move_generator.getPawnMoves(game_state, field_before);
  vector<Move> expected_moves = {};

  ASSERT_TRUE(expectedMovesInMoves(pawn_moves, expected_moves));
}

TEST(MoveGenerator, test_b_pawn_moves_ground_blocked_one) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 49;
  game_state.board.fields[field_before] = Piece::black_pawn;
  game_state.board.fields[33] = Piece::black_knight;

  auto pawn_moves = move_generator.getPawnMoves(game_state, field_before);
  vector<Move> expected_moves = {{field_before, 41, Piece::left_piece}};

  ASSERT_TRUE(expectedMovesInMoves(pawn_moves, expected_moves));
}

TEST(MoveGenerator, test_b_pawn_moves_ground_free_take_two) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 53;
  game_state.board.fields[field_before] = Piece::black_pawn;
  game_state.board.fields[44] = Piece::white_rook;
  game_state.board.fields[46] = Piece::white_bishop;

  auto pawn_moves = move_generator.getPawnMoves(game_state, field_before);
  vector<Move> expected_moves = {{field_before, 45, Piece::left_piece},
                                 {field_before, 37, Piece::left_piece},
                                 {field_before, 44, Piece::left_piece},
                                 {field_before, 46, Piece::left_piece}};

  ASSERT_TRUE(expectedMovesInMoves(pawn_moves, expected_moves));
}

TEST(MoveGenerator, test_b_pawn_moves_mid_free_not_take) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 46;
  game_state.board.fields[field_before] = Piece::black_pawn;
  game_state.board.fields[37] = Piece::black_pawn;
  game_state.board.fields[30] = Piece::black_pawn;

  auto pawn_moves = move_generator.getPawnMoves(game_state, field_before);
  vector<Move> expected_moves = {{field_before, 38, Piece::left_piece}};

  ASSERT_TRUE(expectedMovesInMoves(pawn_moves, expected_moves));
}

TEST(MoveGenerator, test_b_pawn_moves_border_free_take_right) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 40;
  game_state.board.fields[field_before] = Piece::black_pawn;
  game_state.board.fields[33] = Piece::white_knight;
  game_state.board.fields[47] = Piece::white_knight;
  game_state.board.fields[30] = Piece::white_knight;
  game_state.board.fields[55] = Piece::white_knight;
  game_state.board.fields[31] = Piece::white_knight;

  auto pawn_moves = move_generator.getPawnMoves(game_state, field_before);
  vector<Move> expected_moves = {{field_before, 32, Piece::left_piece},
                                 {field_before, 33, Piece::left_piece}};

  ASSERT_TRUE(expectedMovesInMoves(pawn_moves, expected_moves));
}

TEST(MoveGenerator, test_b_pawn_moves_border_free_take_left) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 31;
  game_state.board.fields[field_before] = Piece::black_pawn;
  game_state.board.fields[22] = Piece::white_rook;
  game_state.board.fields[16] = Piece::white_rook;
  game_state.board.fields[24] = Piece::white_rook;
  game_state.board.fields[32] = Piece::white_rook;
  game_state.board.fields[40] = Piece::white_rook;

  auto pawn_moves = move_generator.getPawnMoves(game_state, field_before);
  vector<Move> expected_moves = {{field_before, 31, Piece::left_piece},
                                 {field_before, 30, Piece::left_piece}};

  ASSERT_TRUE(expectedMovesInMoves(pawn_moves, expected_moves));
}

TEST(MoveGenerator, test_b_pawn_moves_promotion) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 9;
  game_state.board.fields[field_before] = Piece::black_pawn;
  game_state.board.fields[0] = Piece::white_queen;

  auto pawn_moves = move_generator.getPawnMoves(game_state, field_before);
  vector<Move> expected_moves = {{field_before, 0, Piece::black_bishop},
                                 {field_before, 0, Piece::black_queen},
                                 {field_before, 0, Piece::black_rook},
                                 {field_before, 0, Piece::black_knight},
                                 {field_before, 1, Piece::black_bishop},
                                 {field_before, 1, Piece::black_queen},
                                 {field_before, 1, Piece::black_rook},
                                 {field_before, 1, Piece::black_knight}};

  ASSERT_TRUE(expectedMovesInMoves(pawn_moves, expected_moves));
}