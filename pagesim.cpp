#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// A struct that holds information about each frame
struct frame
{
  // The page inside the frame
  int id;
  // The time that the page was last accessed
  int last_accessed;
  // The clock counter associated with each page
  int clock_counter;
};

// A function that prints the state of the frames at the end of the simulation
// and the number of page faults.
void printStats(vector<frame> frames, int faults)
{
  printf("  – Frames:");
  for (int i = 0; i < frames.size(); i++)
  {
    printf(" %d", frames[i].id);
  }
  printf("\n");
  printf("  – Page Faults: %d\n", faults);
}

// A function that implements the clock replacement algorithm
void clock(vector<frame> accessed, int frame_number)
{
  // Initializing a vector of frames
  vector<frame> frames;
  // Initialize the number of faults to 0
  int faults = 0;
  // The index at which the algorithm will check the frame vector
  int check = 0;
  // The index at which a page will be replaced
  int index;

  // Moving through the vector containing the order of page acesses
  for (int i = 0; i < accessed.size(); i++)
  {
    // If frames are not full, add the page to the frame vector
    if (frames.size() < frame_number)
    {
      frame temp;
      temp.id = accessed[i].id;
      temp.clock_counter = accessed[i].clock_counter;
      frames.push_back(temp);
      faults++;
    }
    // If frames are full, do nothing or evict a page.
    else
    {
      // If page is already in frames, do nothing
      int found = 0;
      for (int j = 0; j < frame_number; j++)
      {
        if (frames[j].id == accessed[i].id)
        {
          found = 1;
          frames[j].last_accessed = i;
          //printf("Accessing %d again\n", frames[j].id);
          break;
        }
      }

      // If page is not in frames, find a page to evict
      if (found == 0)
      {
        while (1)
        {
          //printf("Checking page %d, with counter %d\n", frames[check].id, frames[check].clock_counter);
          // If 'clock_counter' is 0 increment it, and give the page a second chance
          if (frames[check].clock_counter == 0)
          {
            //printf("Second chance for page %d\n", frames[check].id);
            frames[check].clock_counter = 1;
            check = (check + 1) % frame_number;
          }
          // If 'clock_counter' is 1, evict the page
          else
          {
            //printf("Frame %d evicted\n", frames[check].id);
            index = check;
            check = (check + 1) % frame_number;
            break;
          }
        }
        // Replace the page in the frame vector
        frames[index] = accessed[i];
        faults++;
      }
    }

/*
    printf("Accessing %d:", accessed[i].id);
    for (int j = 0; j < frames.size(); j++)
    {
      printf(" %d", frames[j].id);
    }
    printf("\n");
      */
  }

  // Print the final state of the frames and the number of page faults
  printStats(frames, faults);

}

// A function that implements the optimal replacement algorithm
void optimal(vector<frame> accessed, int frame_number)
{
  // Initializing a vector of frames
  vector<frame> frames;
  // Initializing number of page faults to 0
  int faults = 0;

  // Moving through the vector of accessed pages
  for (int i = 0; i < accessed.size(); i++)
  {
    // If frames are not full, add the page to the frame vector
    if (frames.size() < frame_number)
    {
      frame temp;
      temp.id = accessed[i].id;
      frames.push_back(temp);
      faults++;
    }
    // If frames are full, do nothing or find a page to evict
    else
    {
      // If page is already in frames, do nothing
      int found = 0;
      for (int j = 0; j < frame_number; j++)
      {
        if (frames[j].id == accessed[i].id)
        {
          found = 1;
          printf("Accessing %d again\n", frames[j].id);
          break;
        }
      }
      // If page is not in frames, find a page to evict
      if (found == 0)
      {
        // Index at which to replace the page
        int index;
        // Loop through frames to find out where each page is accessed next
        int last = 0;

        // Find the page that will not be used for the longest time
        for (int j = 0; j < frames.size(); j++)
        {
          int found_again = 0;
          for (int k = i; k < accessed.size(); k++)
          {
            printf("Checking %d against %d\n", frames[j].id, accessed[k].id);
            if (frames[j].id == accessed[k].id)
            {
              printf("Page %d at index %d accessed again at time %d\n", frames[j].id, j, k);
              found_again = 1;
              if (k > last)
              {
                last = k;
                index = j;
                printf("New last = %d at index %d for page %d\n", last, index, frames[j].id);
              }
              break;
            }
          }
          // If the page is not accessed again, replace it
          if (found_again == 0)
          {
            printf("Page %d not found again, evict\n", frames[j].id);
            index = j;
            break;
          }
        }
        /*
        if (found_again == 0)
        {
          index = not_found;
        }
        */
        // Replace the page in the frame vector
        frames[index] = accessed[i];
        faults++;
      }
    }

    printf("Accessing %d:", accessed[i].id);
    for (int j = 0; j < frames.size(); j++)
    {
      printf(" %d", frames[j].id);
    }
    printf("\n\n");

  }
  // Print the final state of the frames and the number of page faults
  printStats(frames, faults);
}

void LRU (vector<frame> accessed, int frame_number)
{
  // Initialize a vector of frames
  vector<frame> frames;
  // Initialize the number of page faults to 0
  int faults = 0;

  // Moving through the vector of accessed pages
  for (int i = 0; i < accessed.size(); i++)
  {
    // If frames are not full, add the page to the frames
    if (frames.size() < frame_number)
    {
      frame temp;
      temp.id = accessed[i].id;
      temp.last_accessed = i;
      frames.push_back(temp);
      faults++;
    }
    // If frames are full, do nothing or find a page to evict
    else
    {
      // If page is already in frames, do nothing
      int found = 0;
      for (int j = 0; j < frame_number; j++)
      {
        if (frames[j].id == accessed[i].id)
        {
          found = 1;
          frames[j].last_accessed = i;
          //printf("Accessing %d again\n", frames[j].id);
          break;
        }
      }

      // If page is not in frames, evict the page that has not been used in
      // the longest amount of time
      if (found == 0)
      {
        int last = i;
        int index;
        for (int j = 0; j < frame_number; j++)
        {
          if (frames[j].last_accessed < last)
          {
            last = frames[j].last_accessed;
            index = j;
          //  printf("Page %d is last accessed, replace at index %d\n", frames[j].id, index);
          }
        }
        // Replace the page at the specified index
        frames[index] = accessed[i];
        frames[index].last_accessed = i;
        faults++;
      }

    }

/*
    printf("Accessing %d:", accessed[i].id);
    for (int j = 0; j < frames.size(); j++)
    {
      printf(" %d", frames[j].id);
    }
    printf("\n\n");
*/

  }
  // Print the final state of the frames and the number of page faults
  printStats(frames, faults);
}

int main (int argc, char * const argv[])
{
  // Handling invalid usage
  if (argc != 2)
  {
    printf("Please enter the number of frames.\n");
    exit(-1);
  }
  int frame_number = atoi(argv[1]);
  printf("Number = %d\n", frame_number);

  // Initializing an array of frames to hold the order of page accesses
  vector<frame> accessed;
  // Reading the order of page accesses from the input file and into the vector
  while (1)
  {
    int num;
    if (scanf("%d", &num) != 1)
      break;
    frame newframe;
    newframe.id = num;
    newframe.clock_counter = 0;
    accessed.push_back(newframe);
  }

  // Delete later
  for (int i = 0; i < accessed.size(); i++)
  {
    printf("%d ", accessed[i].id);
  }
  printf("\n");

  // Run the page simulation with the optimal replacement algorithm
  printf("Optimal:\n");
  optimal(accessed, frame_number);

  // Run the page simulation with the LRU replacement algorithm
  //printf("LRU:\n");
  //LRU(accessed, frame_number);

  // Run the page simulation with the clock replacement algorithm
  //printf("Clock:\n");
  //clock(accessed, frame_number);

}
