#include<cstdio>  
#include<iostream>  
#include<cstdlib>  
#include<algorithm>  
#include<stack>  
#include<queue>  
#include<cstring>  
  
using namespace std;  
  
///�����������Ľ��  
typedef struct tuo_result  
{  
    int course_index;///�γ̺����ַ��������е��±�  
    int score;///�γ̵�ѧ��  
} tuo_result;  
typedef struct tuo_list  //��������õ��Ŀγ��ݶ�  
{  
    tuo_result s[100];  
    int cnt;  
} tuo_list;  
  
char course_id[100][5]; ///�γ̺�  
int score[100];  ///�γ�ѧ�֣��±���γ̺ŵ����±��Ӧ  
int G[100][100]; ///�γ�֮����ڽӾ���  
int term; ///ѧ����  
int credit;///ÿѧ��ѧ������  
int course_sum;///רҵ�γ�����  
  
void prf_tidu(tuo_list *tidu, int tidu_sum);  
void prf_course_fen(int course_fen[][15], int term1);  
  
int judge_course_id_index(char *str); ///�жϿγ̺ŵ��±�  
int scaf(int *temp); ///����  
void add_e(int *temp);///������޹�ϵ  
void crtl_z_e(int *temp);///ȡ�����޹�ϵ  
void temp_copy(int *temp, int *copy_tp);///��һ�� ÿ���γ̵�ֱ��ǰ����������  �ĸ���  
int tuopu_sort(tuo_list *tidu, int &tidu_sum, int *temp);   ///�������򣬲��ҽ��ֺ��ݶ�  
void tidu_copy(tuo_list *tidu, int tidu_sum, tuo_list *copy_t, int copy_sum); ///��һ���ݶȵĸ���  
int course_plan_xijie(tuo_list *tidu, int tidu_cnt, int *c, int &course_cnt, int term_cnt); ///�ſ�ϸ��  
int course_plan1(tuo_list *tidu, int tidu_sum, int course_fen[][15]); ///����ʽ�ſ�  
int course_plan2(tuo_list *tidu, int tidu_sum, int course_fen[][15]); ///ƽ��ʽ�ſ�  
void prf_file(int course_fen[][15], int times); ///д�ļ�����  
///ɾ���γ̺Ŷ�Ӧ�γ���Ϣ  
void dele_course(int &course_sum, int G[][100], int *score, char course_id[][5], int *temp);  
int dele_course_f(int &course_sum, int G[][100], int *score, char course_id[][5], char *name, int *temp);  
///��ӿγ̺�ѧ��  
void add_course(int &course_sum, int G[][100], int *score, char course_id[][5]);  
  
  
int main()  
{  
    while(true)  
    {  
        printf("****************************�Ƿ�����γ���Ϣ��***************************************\n");  
        printf("****************************1: Yes!��Ҫ��������γ���Ϣ��****************************\n");  
        printf("****************************2: No!��Ҫ�˳���*****************************************\n");  
        printf("������ѡ�\n");  
  
        int x;  
        scanf("%d", &x);  
        if(x == 1)  
        {  
  
            ///���룺  
            int temp[100];  ///����γ̹�ϵʱ��¼ÿ�ſε�ֱ��ǰ����  
  
  
            memset(temp, 0, sizeof temp);  
            scaf(temp);  
  
  
            while(true)  
            {  
                printf("******************1):������޹�ϵ��****************************\n");  
                printf("******************2):ȡ��һЩ���޹�ϵ��************************\n");  
                printf("******************3):���γ̼��е�ǰ����ѧ�ڽ��а��š�**********\n");  
                printf("******************4):���γ�ƽ���ֲ�������ѧ�ڽ��а��š�********\n");  
                printf("******************5):����µĿγ̡�****************************\n");  
                printf("******************6):ɾ���γ̡�********************************\n");  
                printf("******************7):�˻���һ��********************************\n");  
                printf("������ѡ��(��ż���)��\n");  
                int xx;  
                scanf("%d", &xx);  
  
                if(xx == 1)  
                    add_e(temp);  
                else if(xx == 2)  
                    crtl_z_e(temp);  
                else if(xx == 3)  
                {  
                    ///��������  
                    int copy_temp[100];  
                    temp_copy(temp, copy_temp);  
                    tuo_list tidu[15];  
                    int tidu_sum;  
                    int re = tuopu_sort(tidu, tidu_sum, copy_temp);  
                    if(re)  
                    {  
                        printf("����������\n");  
                        ///continue;  
                    }  
  
                    ///ѧϰ�����е�ǰ����ѧ��  
                    tuo_list tidu1[15];  
                    int tidu_sum1;  
                    tidu_copy(tidu, tidu_sum, tidu1, tidu_sum1); ///��һ���ݶȵĸ���  
  
                    int course_fen1[15][15]; ///ÿѧ�ڵĿγ̰��ţ�һ�д���һѧ��  
                    if( course_plan1(tidu1, tidu_sum1, course_fen1) )  
                    {  
                        printf("����������\n");  
                        continue;  
                    }  
                    ///����źõĿγ�  
                    prf_course_fen(course_fen1, term);  
  
                    printf("�Ƿ񽫽��д���ļ��У�\n");  
                    printf("********1��Yes********\n");  
                    printf("********2��No*********\n");  
                    printf("������ѡ�\n");  
                    int xxx;  
                    scanf("%d", &xxx);  
                    if(xxx == 1)  
                        prf_file(course_fen1, 1);  
                }  
                else if(xx == 4)  
                {  
                    ///��������  
                    int copy_temp[100];  
                    temp_copy(temp, copy_temp);  
                    tuo_list tidu[15];  
                    int tidu_sum;  
                    int re = tuopu_sort(tidu, tidu_sum, copy_temp);  
                    if(re)  
                    {  
                        printf("����������\n");  
                        continue;  
                    }  
  
                    ///ѧϰ����ƽ���ֲ�ÿ��ѧ��  
                    tuo_list tidu2[15];  
                    int tidu_sum2;  
                    tidu_copy(tidu, tidu_sum, tidu2, tidu_sum2); ///��һ���ݶȵĸ���  
  
                    int course_fen2[15][15];///ÿѧ�ڵĿγ̰��ţ�һ�д���һѧ��  
                    if( course_plan2(tidu2, tidu_sum2, course_fen2) )  
                    {  
                        printf("����������\n");  
                        continue;  
                    }  
                    ///����źõĿγ�  
                    prf_course_fen(course_fen2, term);  
  
                    printf("�Ƿ񽫽��д���ļ��У�\n");  
                    printf("********1��Yes********\n");  
                    printf("********2��No*********\n");  
                    printf("������ѡ�\n");  
                    int xxx;  
                    scanf("%d", &xxx);  
                    if(xxx == 1)  
                        prf_file(course_fen2, 0);  
                }  
                else if(xx == 5){  
                    add_course(course_sum, G, score, course_id);  
                }  
                else if(xx == 6){  
                    dele_course( course_sum, G, score, course_id, temp);  
                }  
                else if(xx == 7)  
                    break;  
                else  
                    printf("�����������������롣\n");  
            }  
        }  
        else if(x == 2)  
        {  
            printf("�ټ�����ӭ�´�ʹ�ã�\n");  
            break;  
        }  
        else  
                printf("�����������������롣\n");  
    }  
    return 0;  
}  
  
///ɾ���γ̺Ŷ�Ӧ�γ���Ϣ  
void dele_course(int &course_sum, int G[][100], int *score, char course_id[][5], int *temp){  
    printf("������Ҫɾ���Ŀγ���Ŀ��\n");  
    int n;  
    scanf("%d", &n);  
  
    char name[100];  
    for(int i = 0; i < n; i++){  
        printf("������Ҫɾ���ĵ�%d���γ̺ţ�\n", i+1);  
        scanf(" %s", name);  
        int re = dele_course_f(course_sum, G, score, course_id, name, temp);  
        if(re == 1){  
            printf("ɾ���ɹ���\n");  
        }  
        else{  
            printf("ɾ��ʧ�ܣ�\n");  
        }  
    }  
}  
int dele_course_f(int &course_sum, int G[][100], int *score, char course_id[][5], char *name, int *temp){  
  
    char cour_temp[100][5];  
    int G_temp[100][100];  
  
    ///��¼Ҫɾ���Ŀγ̺��±�  
    int numb = judge_course_id_index(name);  
    if(numb == -1){  
        printf("����γ̺�û�ҵ�������׼ȷ������������룡\n");  
        return 0;  
    }  
  
    ///��ԭ�ȿγ̺�������һ������  
    for(int i = 0; i < course_sum; i++){  
        int temp_j=0;  
        for(int j=0; course_id[i][j] != '\0'; j++){  
            cour_temp[i][j] = course_id[i][j];  
            temp_j = j;  
        }  
        cour_temp[i][temp_j+1] = '\0';  
    }  
    ///�����µĿγ̺�����  
    for(int i=numb; i<course_sum-1; i++){  
        int temp_k=0;  
        for(int k=0; course_id[i+1][k]!='\0'; k++){  
            course_id[i][k] = course_id[i+1][k];  
            temp_k=k;  
        }  
        course_id[i][temp_k+1]='\0';  
    }  
  
    ///���������µĿγ����޹�ϵ�ڽӱ�д��G_temp��  
    for(int i=0; i<course_sum; i++){  
        temp[i]=0;  
    }  
    for(int i=0; i<course_sum; i++){  
        if(i == numb) continue;  
        for(int j=0; j<course_sum; j++){  
            if(j == numb)   continue;  
  
            if(G[i][j]){  
                int s1, s2;  
                s1 = judge_course_id_index(cour_temp[i]);  
                s2 = judge_course_id_index(cour_temp[j]);  
                G_temp[s1][s2] = 1;  
                temp[s2]++;  
            }  
  
        }  
    }  
    ///���µĿγ����޹�ϵ�ڽӱ�д��G[][]��  
    for(int i=0; i<course_sum-1; i++){  
        for(int j=0; j<course_sum-1; j++){  
            G[i][j] = G_temp[i][j];  
        }  
    }  
  
    ///ɾ������Ҫɾ���Ŀγ̺ŵ�ѧ��  
    for(int i=numb; i < course_sum-1; i++){  
        score[i] = score[i+1];  
    }  
    course_sum--;  
    return 1;  
}  
  
///��ӿγ̺�ѧ��  
void add_course(int &course_sum, int G[][100], int *score, char course_id[][5]){  
    printf("������Ҫ��ӵĿγ���Ŀ��\n");  
    int n;  
    scanf("%d", &n);  
  
    char name[100];  
    int scor;  
    for(int i = 0; i < n; i++){  
        printf("�������%d���γ̵����ƺ�ѧ�֣���ʽΪ��name score\n", i+1);  
        scanf(" %s %d", name, &scor);  
        score[course_sum] = scor;  
        for(int k=0; name[k]!='\0'; k++){  
            course_id[course_sum][k]=name[k];  
        }  
        printf("��ӳɹ���\n");  
    }  
    course_sum++;  
}  
  
void prf_file(int course_fen[][15], int flag)  
{  
    FILE *fp;  
    if( (fp = fopen("file.txt", "a")) == NULL)  
        printf("�ļ���ʧ��\n");  
    if(flag == 1)  
        fputs("ƽ���ֲ�", fp);  
    else  
        fputs("����ʽ", fp);  
    fputs("ʽ�γ̰���:\n", fp);  
    for(int i = 0; i < term; i++)  
    {  
        char ch = i + 1 + '0';  
        fputc(ch, fp);  
        fputs("ѧ�ڵĿγ̣�\n", fp);  
        for(int j = 0; course_fen[i][j] >= 0; j++)  
            fputs(course_id[course_fen[i][j]], fp);  
        fputc('\n', fp);  
    }  
    fputs("\n\n", fp);  
    fclose(fp);  
}  
  
void crtl_z_e(int *temp)  
{  
    printf("������Ҫȡ�������޹�ϵ��������\n");  
    int n;  
    char str1[5], str2[5];  
    scanf("%d", &n);  
    printf("������Ҫȡ�������޹�ϵ��ȡ��s2 �����޿� s1 �����޹�ϵ�������ʽΪ��s1  s2\n");  
    printf("�����룺\n");  
    for(int i = 0; i < n; i++)  
    {  
        scanf(" %s %s", str1, str2);  
        int s1, s2;  
        s1 = judge_course_id_index(str1);  
        s2 = judge_course_id_index(str2);  
        if(!G[s1][s2])  
        {  
            printf("%s �� %s �����޹�ϵ���˴��������ϣ���������롣\n", str1, str2);  
            continue;  
        }  
        else  
        {  
            G[s1][s2] = 0;  
            temp[s2]--;  
        }  
    }  
}  
void add_e(int *temp)  
{  
    printf("������Ҫ��ӵ����޹�ϵ��������\n");  
    int n;  
    char str1[5], str2[5];  
    scanf("%d", &n);  
    printf("������Ҫ��ӵ����޹�ϵ�����s2 �����޿� s1 �����޹�ϵ�������ʽΪ��s1  s2\n");  
    printf("�����룺\n");  
    for(int i = 0; i < n; i++)  
    {  
        scanf(" %s %s", str1, str2);  
        int s1, s2;  
        s1 = judge_course_id_index(str1);  
        s2 = judge_course_id_index(str2);  
        if(G[s1][s2])  
        {  
            printf("%s �� %s �Ѵ������޹�ϵ���˴��������ϣ���������롣\n", str1, str2);  
            continue;  
        }  
        else  
        {  
            G[s1][s2] = 1;  
            temp[s2]++;  
        }  
    }  
}  
void temp_copy(int *temp, int *copy_tp)  
{  
    for(int i = 0; i < course_sum; i++)  
        copy_tp[i] = temp[i];  
}  
  
void tidu_copy(tuo_list *tidu, int tidu_sum, tuo_list *copy_t, int copy_sum)  
{  
    copy_sum = tidu_sum;  
    for(int i = 0; i < tidu_sum; i++)  
    {  
        copy_t[i].cnt = tidu[i].cnt;  
        for(int j = 0; j < tidu[i].cnt; j++)  
        {  
            copy_t[i].s[j].course_index = tidu[i].s[j].course_index;  
            copy_t[i].s[j].score = tidu[i].s[j].score;  
        }  
    }  
}  
  
int course_plan_xijie(tuo_list *tidu, int tidu_cnt, int *c, int &course_cnt, int term_cnt, int course_max)  
{  
    int course_num = 0;  
  
    int c_score = 0;///һѧ�����ſε���ѧ��  
  
    int c_i = 0;  
    tuo_result *s = tidu[tidu_cnt].s;  
  
  
    int s_i = 0, i;  
    for(i = 0; i < tidu[tidu_cnt].cnt; i++)  
    {  
        if(c_score + s[i].score <= credit)  
        {  
            c[c_i++] = s[i].course_index;  
            c_score += s[i].score;  
  
            course_cnt++;  
            course_num++;  
        }  
        else  
        {  
            s[s_i].course_index = s[i].course_index;  
            s[s_i++].score = s[i].score;  
        }  
        if(course_num >= course_max || (course_sum - course_cnt) <= (term - term_cnt))  
        {  
            for(i++ ; i < tidu[tidu_cnt].cnt; i++)  
            {  
                s[s_i].course_index = s[i].course_index;  
                s[s_i++].score = s[i].score;  
            }  
            tidu[tidu_cnt].cnt = s_i;  
            return 1;  
        }  
    }  
    tidu[tidu_cnt].cnt = s_i;  
  
    for(int i = 1; i < tidu_cnt+2; i += 2)  
    {  
        s = tidu[i].s;  
        s_i = 0;  
        for(int j = 0; j < tidu[i].cnt; j++)  
        {  
            if(c_score + s[j].score <= credit)  
            {  
                c[c_i++] = s[j].course_index;  
                c_score += s[j].score;  
  
                course_cnt++;  
                course_num++;  
            }  
            else  
            {  
                s[s_i].course_index = s[j].course_index;  
                s[s_i++].score = s[j].score;  
            }  
            if(course_num >= course_max || (course_sum - course_cnt) <= (term - term_cnt))  
            {  
                for(j++ ; j < tidu[i].cnt; j++)  
                {  
                    s[s_i].course_index = s[j].course_index;  
                    s[s_i++].score = s[j].score;  
                }  
                tidu[i].cnt = s_i;  
                return 1;  
            }  
        }  
        tidu[i].cnt = s_i;  
    }  
  
    return 0;  
  
}  
  
int course_plan1(tuo_list *tidu, int tidu_sum, int course_fen[][15])  
{  
  
  
    if(course_sum < term)  
    {  
        printf("�����Ŀγ���С��ѧ���������Ϸ�\n");  
        return 1;  
    }  
  
    int i, j, k;  
    for(i = 0; i < 15; i++)///��ʼ��ÿѧ�ڵĿ�  
        for(j = 0; j < 15; j++)  
            course_fen[i][j] = -1;  
    int tidu_cnt = 0, course_cnt = 0;  ///ǰ�߼�¼�ŵ��˵ڼ��ݶȣ� ���߼�¼�������˶��ٿγ�  
    int flag = 0;  
    for(i = 0; i < term; i++)  
    {  
        if( course_plan_xijie(tidu, tidu_cnt, course_fen[i], course_cnt, i+1, credit) )  
        {  
            flag = 1;  
            if(tidu[tidu_cnt].cnt <= 0)  
                tidu_cnt += 2;  
            break;  
        }  
        if(tidu[tidu_cnt].cnt <= 0 && tidu_cnt < tidu_sum-2)  
            tidu_cnt += 2;  
    }  
  
    if(flag)  
    {  
        for(i++ ; i < term && tidu_cnt < tidu_sum; tidu_cnt += 2)  
        {  
            for(j = 0; j < tidu[tidu_cnt].cnt; j++)  
            {  
                course_fen[i++][0] = tidu[tidu_cnt].s[j].course_index;  
                course_cnt++;  
            }  
        }  
        for(j = 1; j < tidu_sum; j += 2)  
        {  
            for(k = 0; k < tidu[j].cnt; k++)  
            {  
                course_fen[i++][0] = tidu[j].s[k].course_index;  
                course_cnt++;  
            }  
        }  
    }  
    else if(course_cnt < course_sum)  
    {  
        printf("����γ���������Ѵﵽÿѧ��ѧ�����ޣ��γ��޷����ꡣ\n");  
        return 1;  
    }  
  
    return 0;  
}  
int course_plan2(tuo_list *tidu, int tidu_sum, int course_fen[][15])  
{  
  
  
    if(course_sum < term)  
    {  
        printf("�����Ŀγ���С��ѧ���������Ϸ�\n");  
        return 1;  
    }  
  
    int i, j;  
    for(i = 0; i < 15; i++)///��ʼ��ÿѧ�ڵĿ�  
        for(j = 0; j < 15; j++)  
            course_fen[i][j] = -1;  
    int tidu_cnt = 0, course_cnt = 0;  ///ǰ�߼�¼�ŵ��˵ڼ��ݶȣ� ���߼�¼�������˶��ٿγ�  
  
    int averge_c = course_sum / term;  
    for(i = 0; i < term; i++)  
    {  
        int x = averge_c;  
        if(i < (course_sum % term))    x = averge_c + 1;  
  
        course_plan_xijie(tidu, tidu_cnt, course_fen[i], course_cnt, i+1, x);  
  
        if(tidu[tidu_cnt].cnt <= 0 && tidu_cnt < tidu_sum - 2)  
            tidu_cnt += 2;  
    }  
  
  
    if(course_cnt < course_sum)  
    {  
        printf("����γ���������Ѵﵽÿѧ��ѧ�����ޣ��γ��޷����ꡣ\n");  
        return 1;  
    }  
  
    return 0;  
}  
  
  
void prf_tidu(tuo_list *tidu, int tidu_sum)  
{  
    printf("\n\n");  
    printf("�ݶȵ�����Ϊ��%d\n", tidu_sum);  
    for(int i = 0; i < tidu_sum; i++)  
    {  
        printf("%d�ݶ��еĿγ̣�\n", i);  
        for(int j = 0; j < tidu[i].cnt; j++)  
            printf("%d ", tidu[i].s[j].course_index);  
        printf("\n");  
    }  
}  
void prf_course_fen(int course_fen[][15], int term1)  
{  
    int i, j;  
    for(i = 0; i < term1; i++)  
    {  
        printf("\n%dѧ�ڵĿγ̣�\n", i+1);  
        for(j = 0; course_fen[i][j] >= 0; j++)  
            printf("%s : %d\n", course_id[course_fen[i][j]], score[course_fen[i][j]]);  
        printf("\n");  
    }  
}  
  
  
int tuopu_sort(tuo_list *tidu, int &tidu_sum, int *temp)  
{  
    int c_sum = 0;///������Ŀγ������ж������Ƿ���ڻ�  
  
    int i, j;  
    tidu_sum = 0;  
    while(true)  
    {  
        tidu[tidu_sum].cnt = 0;///�����γ��ݶȳ�ʼ��  
        tidu[tidu_sum+1].cnt = 0;  
  
  
        ///���������������ɾ�  break;  
        int tt0[100], tt_i = 0, flag = 1;//tt_i  ��¼��һ����ֱ��ǰ��Ϊ0�Ŀγ��±�  
        for(i = 0; i < course_sum; i++)  
            if(temp[i] == 0)  
            {  
                tt0[tt_i++] = i;  
                temp[i]--;  
                flag = 0;  
            }  
        if(flag)  break;  
  
        ///��������֮  ɾ��ͼ��ֱ��ǰ��Ϊ0�Ŀγ�  
        for(i = 0; i < tt_i; i++)  
        {  
            int biao = 1, c = tt0[i];  
            for(j = 0; j < course_sum; j++)  
                if(G[c][j])  
                {  
                    biao = 0;///��ǽ�����Ӱ���  
  
                    temp[j]--;///��������֮ ֱ��ǰ��-1  
                }  
            tidu[tidu_sum+biao].s[tidu[tidu_sum+biao].cnt].course_index = c;  
            tidu[tidu_sum+biao].s[tidu[tidu_sum+biao].cnt++].score = score[c];  
            c_sum++;  
        }  
        tidu_sum += 2;  
    }  
    if(c_sum != course_sum)  
    {  
        printf("������ڻ���\n");  
        return 1;  
    }  
    if(tidu_sum / 2 > term)  
    {  
        printf("���벻�Ϸ������޹�ϵ�����ȴ���ѧ������\n");  
        return 1;  
    }  
    return 0;  
}  
  
  
int judge_course_id_index(char *str)  
{  
    int i = -1;  
    for(i = 0; i < course_sum; i++)  
    {  
        if(strcmp(course_id[i], str) == 0)  
            break;  
    }  
    return i;  
}  
  
int scaf(int *temp)  
{  
    printf("������רҵѧ������\n");  
    scanf("%d", &term);  
  
    printf("������ÿѧ��ѧ�����ޣ�\n");  
    scanf("%d", &credit);  
  
    printf("������רҵ�γ�������\n");  
    scanf("%d", &course_sum);  
  
    printf("��������%d�ſεĿγ̺ţ��̶�3λ���ȵ���ĸ��������ϣ����Կո������\n", course_sum);  
    for(int i = 0; i < course_sum; i++)  
        scanf(" %s", course_id[i]);  
  
    printf("����������%d�ſε�ѧ�֣�\n", course_sum);  
    for(int i = 0; i < course_sum; i++)  
    {  
        scanf("%d", &score[i]);  
        if(score[i] > credit)  
        {  
            printf("����ѧ�ֲ��Ϸ�\n");  
            return 1;  
        }  
    }  
  
    int m, s1 = 0, s2 = 0;  
    char str1[10], str2[10];  
    printf("������γ�֮��Ĺ�ϵ������ϵ�����s1 �� s2 ��ֱ�����޿γ̣��������ʽΪ��s1 s2\n");  
    printf("������γ̹�ϵ����\n");  
    scanf("%d", &m);  
    printf("������γ̹�ϵ��\n");  
    for(int i = 0; i < course_sum; i++)  
        for(int j = 0; j < course_sum; j++)  
            G[i][j] = 0;  
    for(int i = 0; i < m; i++)  
    {  
        scanf(" %s %s", str1, str2);  
        s1 = judge_course_id_index(str1);  
        s2 = judge_course_id_index(str2);  
        if(s1 == s2 || s1 == -1 || s2 == -1)  
            printf("����������������롣\n");  
        else if(G[s1][s2])  
            printf("�ظ����룬���������롣\n");  
        else  
        {  
            G[s1][s2] = 1;  
            temp[s2]++;  
        }  
    }  
    return 0;  
}  

