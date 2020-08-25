#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    // index of winner and loser
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(const int ranks[]);
void add_pairs(void);
void sort_pairs(int inf_lim, int top_lim);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
            preferences[i][j] = 0;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs(0, pair_count - 1);
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; ++i)
    {
        // if vote matches
        if(strcmp(candidates[i], name) == 0)
        {
            // update rank: the voter has the preference rank for the candidate i
            ranks[rank] = i;
            return true;
        }
    }
    // if the vote doesn't match any candidate name, it fails
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(const int ranks[])
{
    // 0 <= i < j < candidate_count
    for (int i = 0; i < candidate_count; ++i)
    {
            // rank[i] index of the ith preferred candidate
        for (int j = (i + 1); j < candidate_count; ++j)
        {
            // rank[j] index of jth preferred candidate of the list
            // increase the number of voter that prefer candidate rank[i] over candidate rank[j]
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; ++i)
    {
        for (int j = i+1; j < candidate_count; ++j) {
            if(preferences[i][j] > preferences[j][i])
            {
                // i wins over j
                pair newPair;
                newPair.winner = i;
                newPair.loser = j;
                // store pair to the address pair_count and then increase pair_count
                pairs[pair_count++] = newPair;
            }
            else if(preferences[j][i] > preferences[i][j])
            {
                // j wins over i
                pair newPair;
                newPair.winner = j;
                newPair.loser = i;
                // store pair to the address pair_count and then increase pair_count
                pairs[pair_count++] = newPair;
            }
            else
            {
                // i and j are even
                // nothing to do
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(int inf_lim, int top_lim)
{
    // if length = 1 : already sorted
    if ((inf_lim - top_lim) == 1)
    {
        return;
    }
    // get the middle of the current portion
    int middle = inf_lim + ((top_lim - inf_lim)/2);
    // sort left before middle
    sort_pairs(inf_lim, middle - 1);
    // sort right from middle
    sort_pairs(middle, top_lim);

    // merge left and right
    int numberOfPairToOrder = top_lim - inf_lim + 1;
    int numberOfOrderedPairToCopy = numberOfPairToOrder;
    // temporary array
    pair subOrderedPairs[numberOfPairToOrder];
    // merging sorting left and right
    int indexLeft = inf_lim;
    int indexRight = middle;
    int i = 0;
    while(numberOfPairToOrder != 0)
    {
        bool isMiddleReached = indexLeft + i == middle;
        bool isLeftBiggerThanRight = pairs[indexLeft].winner > pairs[indexRight].winner;
        bool isLeftFirst = !isMiddleReached && isLeftBiggerThanRight;
        subOrderedPairs[i].winner = isLeftFirst ? pairs[indexLeft].winner : pairs[indexRight].winner;
        subOrderedPairs[i].loser = isLeftFirst ? pairs[indexLeft].loser : pairs[indexRight].loser;
        i++;
        numberOfPairToOrder--;
    }
    // subArray is now sorted : erase values in pairs array for this range
    for (int j = 0; j < numberOfOrderedPairToCopy; ++j) {
        pairs[inf_lim + j] = subOrderedPairs[j];
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}
