#include "gtest/gtest.h"
#include "helper_for_tests.h"
#include "source/calculation/game_state_controller.h"
#include "source/calculation/move_generator.h"

using namespace blaengine::calculation;

TEST(KnightMoves, test_general_moves_all) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 27;
  game_state.board.fields[field_before] = Piece::white_knight;

  auto knight_moves = move_generator.getKnightMoves(game_state, field_before);
  vector<Move> expected_moves = {{field_before, 17, Piece::left_piece},
                                 {field_before, 10, Piece::left_piece},
                                 {field_before, 12, Piece::left_piece},
                                 {field_before, 21, Piece::left_piece},
                                 {field_before, 37, Piece::left_piece},
                                 {field_before, 44, Piece::left_piece},
                                 {field_before, 42, Piece::left_piece},
                                 {field_before, 33, Piece::left_piece}};

  ASSERT_TRUE(expectedMovesInMoves(knight_moves, expected_moves));
}

TEST(KnightMoves, test_general_moves_pos0) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 0;
  game_state.board.fields[field_before] = Piece::black_knight;

  auto knight_moves = move_generator.getKnightMoves(game_state, field_before);
  vector<Move> expected_moves = {{field_before, 17, Piece::left_piece},
                                 {field_before, 10, Piece::left_piece}};

  ASSERT_TRUE(expectedMovesInMoves(knight_moves, expected_moves));
}

TEST(KnightMoves, test_general_moves_pos7) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 7;
  game_state.board.fields[field_before] = Piece::white_knight;

  auto knight_moves = move_generator.getKnightMoves(game_state, field_before);
  vector<Move> expected_moves = {{field_before, 13, Piece::left_piece},
                                 {field_before, 22, Piece::left_piece}};

  ASSERT_TRUE(expectedMovesInMoves(knight_moves, expected_moves));
}

TEST(KnightMoves, test_general_moves_pos63) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 63;
  game_state.board.fields[field_before] = Piece::black_knight;

  auto knight_moves = move_generator.getKnightMoves(game_state, field_before);
  vector<Move> expected_moves = {{field_before, 53, Piece::left_piece},
                                 {field_before, 46, Piece::left_piece}};

  ASSERT_TRUE(expectedMovesInMoves(knight_moves, expected_moves));
}

TEST(KnightMoves, test_general_moves_pos56) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 56;
  game_state.board.fields[field_before] = Piece::white_knight;

  auto knight_moves = move_generator.getKnightMoves(game_state, field_before);
  vector<Move> expected_moves = {{field_before, 41, Piece::left_piece},
                                 {field_before, 50, Piece::left_piece}};

  ASSERT_TRUE(expectedMovesInMoves(knight_moves, expected_moves));
}

TEST(KnightMoves, test_general_moves_pos24) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 24;
  game_state.board.fields[field_before] = Piece::black_knight;

  auto knight_moves = move_generator.getKnightMoves(game_state, field_before);
  vector<Move> expected_moves = {{field_before, 41, Piece::left_piece},
                                 {field_before, 34, Piece::left_piece},
                                 {field_before, 9, Piece::left_piece},
                                 {field_before, 18, Piece::left_piece}};

  ASSERT_TRUE(expectedMovesInMoves(knight_moves, expected_moves));
}

TEST(KnightMoves, test_general_moves_pos55) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 55;
  game_state.board.fields[field_before] = Piece::white_knight;

  auto knight_moves = move_generator.getKnightMoves(game_state, field_before);
  vector<Move> expected_moves = {{field_before, 61, Piece::left_piece},
                                 {field_before, 45, Piece::left_piece},
                                 {field_before, 38, Piece::left_piece}};

  ASSERT_TRUE(expectedMovesInMoves(knight_moves, expected_moves));
}

TEST(KnightMoves, test_general_moves_pos3) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 3;
  game_state.board.fields[field_before] = Piece::black_knight;

  auto knight_moves = move_generator.getKnightMoves(game_state, field_before);
  vector<Move> expected_moves = {{field_before, 9, Piece::left_piece},
                                 {field_before, 18, Piece::left_piece},
                                 {field_before, 20, Piece::left_piece},
                                 {field_before, 13, Piece::left_piece}};

  ASSERT_TRUE(expectedMovesInMoves(knight_moves, expected_moves));
}

TEST(KnightMoves, test_w_moves_piece_taking) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 45;
  game_state.board.fields[field_before] = Piece::white_knight;
  game_state.board.fields[51] = Piece::white_knight;
  game_state.board.fields[60] = Piece::black_knight;
  game_state.board.fields[62] = Piece::white_queen;
  game_state.board.fields[55] = Piece::black_pawn;
  game_state.board.fields[39] = Piece::white_king;
  game_state.board.fields[30] = Piece::white_bishop;
  game_state.board.fields[28] = Piece::black_rook;
  game_state.board.fields[35] = Piece::white_rook;

  auto knight_moves = move_generator.getKnightMoves(game_state, field_before);
  vector<Move> expected_moves = {{field_before, 60, Piece::left_piece},
                                 {field_before, 55, Piece::left_piece},
                                 {field_before, 28, Piece::left_piece}};

  ASSERT_TRUE(expectedMovesInMoves(knight_moves, expected_moves));
}

TEST(KnightMoves, test_b_moves_piece_taking) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 45;
  game_state.board.fields[field_before] = Piece::black_knight;
  game_state.board.fields[51] = Piece::black_knight;
  game_state.board.fields[60] = Piece::white_knight;
  game_state.board.fields[62] = Piece::black_queen;
  game_state.board.fields[55] = Piece::white_pawn;
  game_state.board.fields[39] = Piece::black_king;
  game_state.board.fields[30] = Piece::black_rook;
  game_state.board.fields[28] = Piece::white_rook;
  game_state.board.fields[35] = Piece::black_rook;

  auto knight_moves = move_generator.getKnightMoves(game_state, field_before);
  vector<Move> expected_moves = {{field_before, 60, Piece::left_piece},
                                 {field_before, 55, Piece::left_piece},
                                 {field_before, 28, Piece::left_piece}};

  ASSERT_TRUE(expectedMovesInMoves(knight_moves, expected_moves));
}

TEST(KnightMoves, test_moves_no_moves) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 0;
  game_state.board.fields[field_before] = Piece::black_knight;
  game_state.board.fields[17] = Piece::black_knight;
  game_state.board.fields[10] = Piece::black_pawn;

  auto knight_moves = move_generator.getKnightMoves(game_state, field_before);
  vector<Move> expected_moves = {};

  ASSERT_TRUE(expectedMovesInMoves(knight_moves, expected_moves));
}
