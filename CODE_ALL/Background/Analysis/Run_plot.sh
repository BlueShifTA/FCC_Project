# Program to Run Plot 
# By Surapat EK-IN 
# Written on 25/1/2016

for ind_dir in `seq 1 3` ; do
    cp -a Combine_HTBin_wzjet_${ind_dir}.C ${ind_dir}/
    cd ${ind_dir}/
    mkdir plot_${1}
    #sed s/result.root/result_${ind_dir}.root/g Combine_HTBin_wzjet.C > Combine_HTBin_wzjet_${ind_dir}.C 
    root -l <<EOF
        .L Combine_HTBin_wzjet_${ind_dir}.C
        Combine_HTBin()
        .q
EOF
    mv *pdf plot_${1}
    cd ../
done 
