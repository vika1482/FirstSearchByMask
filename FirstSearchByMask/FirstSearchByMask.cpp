#include <iostream>
int FindMaskRec(char* mask, char* input, bool wasstar, int res, int i, int j);
int FindMask(char* mask, char* input, int i);
int masksize(char* s);
int inpsize(char* s, int i);

int main()
{
	char s[255];
	char mask[255];
	char f[] = "%s";
	char fd[] = "%d";

	std::cout << "String: ";
	std::cin.getline(s, 255);
	std::cout << "Mask: ";
	std::cin.getline(mask, 255);
	std::cout << "Result: " << FindMask(mask, s, 0);

}

int FindMaskRec(char* mask, char* input, bool wasstar, int res, int i, int j)
{
	if (input[i] == '\0' || input[i] == ' ')
	{
		while (mask[j] != '\0')
		{
			if (mask[j] != '*')
			{
				if (input[i] == ' ') return FindMask(mask, input, i + 1);
				else return -1;
			}
			j++;
		}
		return res;
	}
	else if (mask[j] == '\0')
	{
		if (mask[j - 1] == '*') return res;
		else
		{
			while (input[i] != ' ' && input[i] != '\0') i++;
			if (input[i] == ' ') return FindMask(mask, input, i + 1);
			else return -1;
		}
	}
	else if (mask[j] == '*')
	{
		if (res != -1) return FindMaskRec(mask, input, true, res, i, ++j);
		else return FindMaskRec(mask, input, true, i, i, ++j);
	}
	else if (mask[j] == '?')
	{
		if (wasstar)
		{
			if (mask[j + 1] == '\0') return res;
			else return FindMaskRec(mask, input, true, res, i + 1, ++j);
		}
		else
		{
			if (res != -1) return FindMaskRec(mask, input, false, res, i + 1, ++j);
			else return FindMaskRec(mask, input, false, i, i + 1, ++j);
		}
	}
	else if (mask[j] == input[i])
	{
		if (res != -1) return FindMaskRec(mask, input, false, res, i + 1, ++j);
		else return FindMaskRec(mask, input, false, i, i + 1, ++j);
	}
	else if (wasstar) return FindMaskRec(mask, input, true, res, i + 1, j);
	else
	{
		bool found = false;
		while (j >= 0)
		{
			if (mask[j] == '*')
			{
				found = true;
				break;
			}
			j--;
		}
		if (found) return FindMaskRec(mask, input, true, res, i + 1, ++j);
		else
		{
			while (input[i] != ' ' && input[i] != '\0') i++;
			if (input[i] == ' ') return FindMask(mask, input, i + 1);
			else return -1;
		}
	}
}

int FindMask(char* mask, char* inp, int i)
{
	int inps = inpsize(inp, i);
	if (masksize(mask) > inps)
	{
		if (inp[i + inps] == ' ')
		{
			i += inps + 1;
			return FindMask(mask, inp, i);
		}
		else return -1;
	}
	else return FindMaskRec(mask, inp, false, -1, i, 0);
}

int masksize(char* s)
{
	int i = 0;
	int size = 0;
	while (s[i] != '\0')
	{
		if (s[i] != '*')
			size++;
		i++;
	}
	return size;
}

int inpsize(char* s, int i)
{
	int size = 0;
	while (s[i] != ' ' && s[i] != '\0')
	{
		i++;
		size++;
	}
	return i;
}