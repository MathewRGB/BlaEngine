#include "gtest/gtest.h"
#include "helper_for_tests.h"
#include "source/calculation/move_generator.h"

using namespace blaengine::calculation;

TEST(RookMoves, test_general_moves_pos35) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 35;
  game_state.board[field_before] = Piece::white_rook;
  vector<ushort> possible_fields = {43, 51, 59, 27, 19, 11, 3,
                                    36, 37, 38, 39, 32, 33, 34};

  auto knight_moves = move_generator.getRookMoves(game_state, field_before);
  auto expected_moves = createMovesFromFieldList(field_before, possible_fields);

  ASSERT_TRUE(expectedMovesInMoves(knight_moves, expected_moves));
}

TEST(RookMoves, test_no_move_possible) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 18;
  game_state.board[field_before] = Piece::white_rook;
  game_state.board[17] = Piece::white_king;
  game_state.board[26] = Piece::white_pawn;
  game_state.board[19] = Piece::white_queen;
  game_state.board[10] = Piece::white_rook;

  auto knight_moves = move_generator.getRookMoves(game_state, field_before);

  ASSERT_TRUE(expectedMovesInMoves(knight_moves, {}));
}

TEST(RookMoves, test_general_moves_pos56) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 56;
  game_state.board[field_before] = Piece::black_rook;
  game_state.board[60] = Piece::white_pawn;
  game_state.board[40] = Piece::black_knight;
  vector<ushort> possible_fields = {57, 58, 59, 60, 48};

  auto knight_moves = move_generator.getRookMoves(game_state, field_before);
  auto expected_moves = createMovesFromFieldList(field_before, possible_fields);

  ASSERT_TRUE(expectedMovesInMoves(knight_moves, expected_moves));
}

TEST(RookMoves, test_general_moves_pos37) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 37;
  game_state.board[field_before] = Piece::black_rook;
  game_state.board[45] = Piece::white_pawn;
  game_state.board[34] = Piece::black_knight;
  vector<ushort> possible_fields = {45, 29, 21, 13, 5, 38, 39, 36, 35};

  auto knight_moves = move_generator.getRookMoves(game_state, field_before);
  auto expected_moves = createMovesFromFieldList(field_before, possible_fields);

  ASSERT_TRUE(expectedMovesInMoves(knight_moves, expected_moves));
}

TEST(RookMoves, test_general_moves_pos50) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 50;
  game_state.board[field_before] = Piece::white_rook;
  game_state.board[42] = Piece::black_queen;
  game_state.board[52] = Piece::white_rook;
  vector<ushort> possible_fields = {58, 42, 49, 48, 51};

  auto knight_moves = move_generator.getRookMoves(game_state, field_before);
  auto expected_moves = createMovesFromFieldList(field_before, possible_fields);

  ASSERT_TRUE(expectedMovesInMoves(knight_moves, expected_moves));
}

TEST(RookMoves, test_general_moves_pos14) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 14;
  game_state.board[field_before] = Piece::black_rook;
  game_state.board[38] = Piece::black_knight;
  game_state.board[10] = Piece::white_knight;
  vector<ushort> possible_fields = {22, 30, 6, 15, 13, 12, 11, 10};

  auto knight_moves = move_generator.getRookMoves(game_state, field_before);
  auto expected_moves = createMovesFromFieldList(field_before, possible_fields);

  ASSERT_TRUE(expectedMovesInMoves(knight_moves, expected_moves));
}
