/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    // yes, I know using divide and conquer would have been better


    // Assuming I can mutate lists bc mut ref
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode* ret = nullptr;
        ListNode* tail = nullptr;

        // Remove empty lists
        auto end_it = std::remove(lists.begin(), lists.end(), nullptr);
        lists.erase(end_it, lists.end());
        if (lists.empty())
            return nullptr;

        // First element
        int min = lists[0]->val;
        int min_i = 0;
        for (int i = 1 ; i < lists.size(); i++) {
            if (lists[i]->val < min) {
                min = lists[i]->val;
                min_i = i;
            }
        }
        ret = tail = lists[min_i];
        if ((lists[min_i] = lists[min_i]->next) == nullptr) {
            lists[min_i] = (lists.back());
            lists.pop_back();
        }

        while (!lists.empty()) {
            min = lists[0]->val;
            min_i = 0;
            for (int i = 1 ; i < lists.size(); i++)
                if (lists[i] && lists[i]->val < min) {
                    min = lists[i]->val;
                    min_i = i;
                }

            tail = (tail->next = lists[min_i]);
            if ((lists[min_i] = lists[min_i]->next) == nullptr) {
                lists[min_i] = lists.back();
                lists.pop_back();
            }
        }

        return ret;
    }
};