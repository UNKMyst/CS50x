#include <cs50.h>
#include <stdio.h>
#include <string.h>
// Made By Paclibar Josh, Used for Self Study not for cheating pls don't.
// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
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
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool checkCycle(int end, int start);

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
    // Loop Throught candidates and check if name is there
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // will loop each rank
    for (int i = 0; i < candidate_count; i++)
    {
        // Will Loop another rank after current and increment
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Will loop through each candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // will loop through each candidate after current
        for (int j = i + 1; j < candidate_count; j++)
        {
            // if candidate i is preferred over candidate j, will add pair
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            // if j is preferred over candidate i, will add pair
            else if (preferences[j][i] > preferences[i][j])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // will loop throught all pairs except last, using bubble sort.
    for (int i = pair_count - 1; i >= 0; i--)
    {
        // will Loop through adjacent pair and compare
        for (int j = 0; j <= i - 1; j++)
        {
            // if j pair hass less than j+1 then swap location
            if ((preferences[pairs[j].winner][pairs[j].loser]) < (preferences[pairs[j + 1].winner][pairs[j + 1].loser]))
            {
                pair tempPair = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = tempPair;
            }
        }
    }
    return;
}

// Recursion function to check if cycle exits for lock_pairs
bool checkCycle(int end, int start)
{
    // If cycle is there then return true
    if (end == start)
    {
        return true;
    }
    // Will loop through candidates and return
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[end][i])
        {
            if (checkCycle(i, start))
            {
                return true;
            }
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Will Loop through pairs and check if there's a cycle
    for (int i = 0; i < pair_count; i++)
    {
        // If no Cycle exist then Lock in pair
        if (!checkCycle(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // Will loop through the candidates and count how many of the locked values are false
    for (int i = 0; i < candidate_count; i++)
    {
        int falseCount = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false)
            {
                falseCount++;
                if (falseCount == candidate_count)
                {
                    printf("%s\n", candidates[i]);
                }
            }
        }
    }
    return;
}
