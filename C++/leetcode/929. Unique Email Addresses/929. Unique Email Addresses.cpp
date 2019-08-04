/******************************************************************************

Every email consists of a local name and a domain name, separated by the @ sign.

For example, in alice@leetcode.com, alice is the local name, and leetcode.com is the domain name.

Besides lowercase letters, these emails may contain '.'s or '+'s.

If you add periods ('.') between some characters in the local name part of an email address, mail sent there will be forwarded to the same address without dots in the local name.  For example, "alice.z@leetcode.com" and "alicez@leetcode.com" forward to the same email address.  (Note that this rule does not apply for domain names.)

If you add a plus ('+') in the local name, everything after the first plus sign will be ignored. This allows certain emails to be filtered, for example m.y+name@email.com will be forwarded to my@email.com.  (Again, this rule does not apply for domain names.)

It is possible to use both of these rules at the same time.

Given a list of emails, we send one email to each address in the list.  How many different addresses actually receive mails? 

 

Example 1:

Input: ["test.email+alex@leetcode.com","test.e.mail+bob.cathy@leetcode.com","testemail+david@lee.tcode.com"]
Output: 2
Explanation: "testemail@leetcode.com" and "testemail@lee.tcode.com" actually receive mails


*******************************************************************************/

#include <iostream>
#include <vector>
#include <set>

using namespace std;

class Solution {
public:
    int numUniqueEmails(vector<string>& emails) {
        set<string> set;
        int pos, i;
        string temp;
        
        for(auto s : emails){
            temp = "";
            pos = s.find('@');
            
            for(i = 0; i < pos; i++){
                if(s[i] == '+') break;
                if(s[i] == '.') continue;
                else temp += s[i];
            }
            
            temp+=s.substr(pos);
            set.insert(temp);
        }
        
        return set.size();
    }
};

int main()
{
    Solution s;
    
    vector<string> emails = {"fg.r.u.uzj+o.pw@kziczvh.com",
                            "r.cyo.g+d.h+b.ja@tgsg.z.com",
                            "fg.r.u.uzj+o.f.d@kziczvh.com",
                            "r.cyo.g+ng.r.iq@tgsg.z.com",
                            "fg.r.u.uzj+lp.k@kziczvh.com",
                            "r.cyo.g+n.h.e+n.g@tgsg.z.com",
                            "fg.r.u.uzj+k+p.j@kziczvh.com",
                            "fg.r.u.uzj+w.y+b@kziczvh.com",
                            "r.cyo.g+x+d.c+f.t@tgsg.z.com",
                            "r.cyo.g+x+t.y.l.i@tgsg.z.com",
                            "r.cyo.g+brxxi@tgsg.z.com",
                            "r.cyo.g+z+dr.k.u@tgsg.z.com",
                            "r.cyo.g+d+l.c.n+g@tgsg.z.com",
                            "fg.r.u.uzj+vq.o@kziczvh.com",
                            "fg.r.u.uzj+uzq@kziczvh.com",
                            "fg.r.u.uzj+mvz@kziczvh.com",
                            "fg.r.u.uzj+taj@kziczvh.com",
                            "fg.r.u.uzj+fek@kziczvh.com"};
    
    cout << s.numUniqueEmails(emails);

    return 0;
}
