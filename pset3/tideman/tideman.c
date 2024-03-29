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
int currentWinner;

// Function prototypes
bool vote(int rank, string name, int ranks[]);

void record_preferences(const int ranks[]);

void add_pairs(void);

void sort_pairs(void);

void merge_sort(int inf_lim, int top_lim);

void lock_pairs(void);

void print_winner(void);

bool isCurrentPairCycling(int j);

bool isCandidateLocked(int candidateIndex);

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
    sort_pairs();
    lock_pairs();

    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; ++i)
    {
        // It is assumed that a voter won't vote 2 times for the same candidate
        if (strcmp(candidates[i], name) == 0)
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
        for (int j = i + 1; j < candidate_count; ++j)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                // i wins over j
                pair newPair;
                newPair.winner = i;
                newPair.loser = j;
                // store pair to the address pair_count and then increase pair_count
                pairs[pair_count++] = newPair;
            }
            else if (preferences[j][i] > preferences[i][j])
            {
                // j wins over i
                pair newPair;
                newPair.winner = j;
                newPair.loser = i;
                // store pair to the address pair_count and then increase pair_count
                pairs[pair_count++] = newPair;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    merge_sort(0, pair_count - 1);
}

void merge_sort(int inf_lim, int top_lim)
{
    if (inf_lim == top_lim)
    {
        return;
    }

    int middle = inf_lim + ((top_lim - inf_lim) / 2);
    int middle_top = middle + 1;
    // sort left
    merge_sort(inf_lim, middle);
    // sort right
    merge_sort(middle_top, top_lim);
    // merge
    int length = top_lim - inf_lim + 1;
    pair temporary_pair[length];

    int indexLeft = inf_lim;
    int indexRight = middle_top;
    for (int i = 0; i < length; ++i)
    {
        if (indexLeft == middle_top)
        {
            // left is empty assign right
            temporary_pair[i] = pairs[indexRight];
            indexRight++;
        }
        else if (indexRight > top_lim)
        {
            // right is empty assign left
            temporary_pair[i] = pairs[indexLeft];
            indexLeft++;
        }
        else if (preferences[pairs[indexLeft].winner][pairs[indexLeft].loser] >
                 preferences[pairs[indexRight].winner][pairs[indexRight].loser])
        {
            // left is bigger assign left
            temporary_pair[i] = pairs[indexLeft];
            indexLeft++;
        }
        else
        {
            // right is bigger assign right
            temporary_pair[i] = pairs[indexRight];
            indexRight++;
        }
    }

    for (int j = 0; j < length; ++j)
    {
        // rewrite original array
        pairs[inf_lim + j] = temporary_pair[j];
    }

}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // lock[i][j] : i wins over j => turn true except if it creates a cycle.
    for (int i = 0; i < pair_count; ++i)
    {
        currentWinner = pairs[i].winner;
        int currentLoser = pairs[i].loser;
        // Does lock[winner][loser] create a cycle ?
        if (!isCurrentPairCycling(currentLoser))
        {
            locked[currentWinner][currentLoser] = true;
        }
    }
}

bool isCurrentPairCycling(int loser)
{
    // base case: if the loser is the currentWinner then it is cycling
    if (loser == currentWinner)
    {
        return true;
    }

    // is the loser locking someone if yes, is it cycling to the currentWinner?
    for (int i = 0; i < candidate_count; ++i)
    {
        if (locked[loser][i] && isCurrentPairCycling(i))
        {
            return true;
        }
    }

    // base case: if the loser isn't locking anyone or if the lock isn't cycling
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; ++i)
    {
        if (!isCandidateLocked(i))
        {
            printf("%s\n", candidates[i]);
        }
    }
}

bool isCandidateLocked(int candidateIndex)
{
    for (int i = 0; i < candidate_count; ++i)
    {
        if (locked[i][candidateIndex])
        {
            return true;
        }
    }
    return false;
}
