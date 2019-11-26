#include "gtest/gtest.h"
#include "helper_for_tests.h"
#include "source/calculation/game_state_controller.h"
#include "source/calculation/move_generator.h"

using namespace blaengine::calculation;

TEST(KingMoves, test_general_moves_pos58) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 58;
  game_state.board.fields[field_before] = Piece::white_king;

  vector<ushort> possible_fields = {57, 49, 50, 51, 59};

  auto knight_moves = move_generator.getKingMoves(game_state, field_before);
  auto expected_moves = createMovesFromFieldList(field_before, possible_fields);

  ASSERT_TRUE(expectedMovesInMoves(knight_moves, expected_moves));
}

TEST(KingMoves, test_general_moves_pos0) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 0;
  game_state.board.fields[field_before] = Piece::black_king;

  vector<ushort> possible_fields = {1, 8, 9};

  auto knight_moves = move_generator.getKingMoves(game_state, field_before);
  auto expected_moves = createMovesFromFieldList(field_before, possible_fields);

  ASSERT_TRUE(expectedMovesInMoves(knight_moves, expected_moves));
}

TEST(KingMoves, test_general_moves_pos3) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 31;
  game_state.board.fields[field_before] = Piece::white_king;

  vector<ushort> possible_fields = {39, 38, 30, 22, 23};

  auto knight_moves = move_generator.getKingMoves(game_state, field_before);
  auto expected_moves = createMovesFromFieldList(field_before, possible_fields);

  ASSERT_TRUE(expectedMovesInMoves(knight_moves, expected_moves));
}

TEST(KingMoves, test_general_moves_pos40) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 40;
  game_state.board.fields[field_before] = Piece::black_king;
  game_state.board.fields[48] = Piece::black_pawn;
  game_state.board.fields[49] = Piece::black_pawn;
  game_state.board.fields[41] = Piece::white_pawn;
  game_state.board.fields[33] = Piece::black_pawn;
  game_state.board.fields[32] = Piece::black_pawn;

  vector<ushort> possible_fields = {41};

  auto knight_moves = move_generator.getKingMoves(game_state, field_before);
  auto expected_moves = createMovesFromFieldList(field_before, possible_fields);

  ASSERT_TRUE(expectedMovesInMoves(knight_moves, expected_moves));
}

TEST(KingMoves, test_general_moves_pos21) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 21;
  game_state.board.fields[field_before] = Piece::white_king;
  game_state.board.fields[29] = Piece::white_pawn;
  game_state.board.fields[30] = Piece::white_pawn;
  game_state.board.fields[22] = Piece::white_pawn;
  game_state.board.fields[14] = Piece::white_pawn;
  game_state.board.fields[13] = Piece::white_pawn;
  game_state.board.fields[12] = Piece::white_pawn;
  game_state.board.fields[20] = Piece::white_pawn;
  game_state.board.fields[28] = Piece::white_pawn;

  vector<ushort> possible_fields = {};

  auto knight_moves = move_generator.getKingMoves(game_state, field_before);
  auto expected_moves = createMovesFromFieldList(field_before, possible_fields);

  ASSERT_TRUE(expectedMovesInMoves(knight_moves, expected_moves));
}

TEST(KingMoves, test_general_moves_pos25) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 25;
  game_state.board.fields[field_before] = Piece::white_king;
  game_state.board.fields[33] = Piece::left_piece;
  game_state.board.fields[34] = Piece::white_pawn;
  game_state.board.fields[26] = Piece::white_pawn;
  game_state.board.fields[18] = Piece::black_pawn;
  game_state.board.fields[17] = Piece::white_pawn;
  game_state.board.fields[16] = Piece::black_pawn;
  game_state.board.fields[24] = Piece::white_pawn;
  game_state.board.fields[32] = Piece::white_pawn;

  vector<ushort> possible_fields = {16, 18, 33};

  auto knight_moves = move_generator.getKingMoves(game_state, field_before);
  auto expected_moves = createMovesFromFieldList(field_before, possible_fields);

  ASSERT_TRUE(expectedMovesInMoves(knight_moves, expected_moves));
}
