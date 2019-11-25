#include "gtest/gtest.h"
#include "helper_for_tests.h"
#include "source/calculation/game_state_controller.h"
#include "source/calculation/move_generator.h"

using namespace blaengine::calculation;

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
