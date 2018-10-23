{% for host_call in host_calls -%}
extern unsigned long long int {{host_call}}_stub( unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int);
unsigned long long int {{host_call}}{{function_name}}_stub( unsigned long long int a, unsigned long long int b, unsigned long long int c, unsigned long long int d, unsigned long long int e, unsigned long long int f){
    return {{host_call}}_stub(a, b, c, d, e, f);
}

{% endfor %}



__attribute__((naked)) unsigned long long int {{function_name}}(void)
{
    asm(
        {% for ins in fct_cont -%}
            "{{ ins }}\n\t"
        {% endfor %}
    );
}
