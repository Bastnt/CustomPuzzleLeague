
// games per match
#define GC_GAMES_PER_MATCH               (3)

// the play area dimensions; GC_SAFE_HEIGHT - 1 is the board height
#define GC_PLAY_WIDTH                    (6)
#define GC_PLAY_HEIGHT                   (45)
#define GC_SAFE_HEIGHT                   (13)
#define GC_GRID_SIZE                     (GC_PLAY_WIDTH * GC_PLAY_HEIGHT)

// object stores
#define GC_BLOCK_STORE_SIZE              (GC_GRID_SIZE)
#define GC_GARBAGE_STORE_SIZE            (2 * GC_PLAY_HEIGHT)
#define GC_COMBO_TABULATOR_STORE_SIZE    (8)
#define GC_GARBAGE_QUEUE_SIZE            (8)

// time steps per second
#define GC_STEPS_PER_SECOND              (50)

// milliseconds per time step
#define GC_TIME_STEP_PERIOD              (1000 / GC_STEPS_PER_SECOND)

// number of subdivisions per grid location
#define GC_STEPS_PER_GRID                (60)

// names
#define GC_PLAYER_NAME_LENGTH            (256)
#define GC_DEFAULT_PLAYER_NAME           "NamelessOne"

// velocity of falling; must be a factor of GC_STEPS_PER_GRID
#define GC_FALL_VELOCITY                 (20)

// velocity and time length of swapping
#define GC_SWAP_VELOCITY                 (10)
#define GC_SWAP_DELAY                    (GC_STEPS_PER_GRID / GC_SWAP_VELOCITY)

// velocity of creep
#define GC_CREEP_DELAY                   (1200)
#define GC_CREEP_ADVANCE_TIMER_STEP      GC_CREEP_DELAY
#define GC_CREEP_TIMER_STEP_INCREMENT    (20)
#define GC_CREEP_INITIAL_TIMER_STEP      GC_CREEP_TIMER_STEP_INCREMENT
#define GC_CREEP_MAX_TIMER_STEP          (2400)
#define GC_CREEP_ADVANCE_VELOCITY        (3)
#define GC_CREEP_INCREMENT_DELAY         (10 * GC_STEPS_PER_SECOND)

// delay between safe height violation and loss
#define GC_LOSS_DELAY                    (7 * GC_STEPS_PER_SECOND)
#define GC_LOSS_DELAY_ELIMINATION        (1 * GC_STEPS_PER_SECOND)

// time length between moves
#define GC_MOVE_DELAY                    (6)

// time length of block dying
#define GC_DYING_DELAY                   (90)

// time length of hanging
#define GC_HANG_DELAY                    (3)

// time length until popping, between popping, and after popping
#define GC_INTERNAL_POP_DELAY            (15)
#define GC_INITIAL_POP_DELAY             (50 + GC_INTERNAL_POP_DELAY)
#define GC_FINAL_POP_DELAY               (50)

// minimum length of a elimination pattern
#define GC_MIN_PATTERN_LENGTH            (3)

// chance of a creep row having a special block
#define GC_NO_SPECIAL_BLOCK_CHANCE_IN    (3)
#define GC_X_NO_SPECIAL_BLOCK_CHANCE_IN  (10)

// chance of garbage shattering to garbage
#define GC_GARBAGE_TO_GARBAGE_SHATTER    (2)

// time length before garbage falls
#define GC_AVERAGE_GARBAGE_DROP_DELAY    (300)
#define GC_SPREAD_GARBAGE_DROP_DELAY     (40)

// time length of the introduction pause; should be multiple of 3
#define GC_START_PAUSE_DELAY             (150)

// maximum height of a garbage block
#define GC_MAX_GARBAGE_HEIGHT            (11)

// score constants
#define GC_MIN_PATTERN_SCORE             (2)
#define GC_GRAY_SCORE                    (3)
#define GC_NUMBER_DIGITS                 (7)
#define GC_MIN_NUMBER_DIGITS_DISPLAYED   (4)
#define GC_MAX_SCORE_INCREMENT_DELAY     (12)
#define GC_MIN_SCORE_INCREMENT_DELAY     (1)
#define GC_SCORE_DELAY_SLOPE             (2)
#define GC_SCORE_REC_LENGTH              (30)
#define GC_SCORE_DEFAULT_TOP_SCORE       (600)
#define GC_SCORE_REC_DEFAULT_NAME        "-----"

// sine constants
#define GC_SINE_TABLE_LENGTH             (100)
#define GC_SINE_TABLE_LOWER_BOUND        (-PI / 2.0f)
#define GC_SINE_TABLE_STEP_WIDTH         (PI / (GC_SINE_TABLE_LENGTH - 1))

// initial swapper location
#define GC_INITIAL_SWAPPER_LOCATION_X    (GC_PLAY_WIDTH / 2 - 1)
#define GC_INITIAL_SWAPPER_LOCATION_Y    (4)

// extreme constants
#define GC_INVISIBLE_MAX_ALPHA           (330)
#define GC_INVISIBLE_MIN_ALPHA           (-20)
#define GC_INVISIBLE_QUICK_DECAY_RATE    (3)
#define GC_INVISIBLE_PULSE_CHANCE_IN     (30)
#define GC_INVISIBLE_PULSE_STRENGTH      (70)
#define GC_CRAZY_LONG_MODE_PERIOD        (150)
#define GC_CRAZY_SHORT_MODE_PERIOD       (50)
#define GC_MAX_WILD_NUMBER               (3)
#define GC_WILD_PERIOD                   (180)
#define GC_WILD_POLYMORPH_PERIOD         (60)
#define GC_MAX_SPECIAL_COLOR_NUMBER      (6)