<HTML><META HTTP-EQUIV="content-type" CONTENT="text/html;charset=utf-8">
<PRE>&lt;!-- This is the project specific website template --&gt;
&lt;!-- It can be changed as liked or replaced by other content --&gt;

&lt;?php

$domain=ereg_replace('[^\.]*\.(.*)$','\1',$_SERVER['HTTP_HOST']);
$group_name=ereg_replace('([^\.]*)\..*$','\1',$_SERVER['HTTP_HOST']);
$themeroot='http://r-forge.r-project.org/themes/rforge/';

echo '&lt;?xml version="1.0" encoding="UTF-8"?&gt;';
?&gt;
&lt;!DOCTYPE html
	PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
	"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd"&gt;
&lt;html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en   "&gt;

  &lt;head&gt;
	&lt;meta http-equiv="Content-Type" content="text/html; charset=UTF-8" /&gt;
	&lt;title&gt;&lt;?php echo $group_name; ?&gt;&lt;/title&gt;
	&lt;link href="&lt;?php echo $themeroot; ?&gt;styles/estilo1.css" rel="stylesheet" type="text/css" /&gt;
  &lt;/head&gt;

&lt;body&gt;

&lt;! --- R-Forge Logo --- &gt;
&lt;table border="0" width="100%" cellspacing="0" cellpadding="0"&gt;
&lt;tr&gt;&lt;td&gt;
&lt;a href="/"&gt;&lt;img src="&lt;?php echo $themeroot; ?&gt;/images/logo.png" border="0" alt="R-Forge Logo" /&gt; &lt;/a&gt; &lt;/td&gt; &lt;/tr&gt;
&lt;/table&gt;


&lt;!-- get project title  --&gt;
&lt;!-- own website starts here, the following may be changed as you like --&gt;

&lt;?php if ($handle=fopen('http://'.$domain.'/export/projtitl.php?group_name='.$group_name,'r')){
$contents = '';
while (!feof($handle)) {
	$contents .= fread($handle, 8192);
}
fclose($handle);
echo $contents; } ?&gt;

&lt;!-- end of project description --&gt;

&lt;?php 
$mon_mess = &lt;&lt;&lt;TEST

RHmm package contains functions for the simulation and the estimation of Hidden Markov Models (HMM) with discrete, univariate and multivariate gaussian, univariate and multivariate mixture of gaussian conditional distributions.

The main functions are:

 - distributionSet and HMMSet to describe the model.
 - HMMSim for the simulation.
 - HMMFit for the estimation.
 - viterbi for computing the Viterbi's path
 - some other graphic functions.

TEST;
echo $mon_mess;

 ?&gt;



&lt;p&gt; The &lt;strong&gt;project summary page&lt;/strong&gt; you can find &lt;a href="http://&lt;?php echo $domain; ?&gt;/projects/&lt;?php echo $group_name; ?&gt;/"&gt;&lt;strong&gt;here&lt;/strong&gt;&lt;/a&gt;. &lt;/p&gt;

&lt;/body&gt;
&lt;/html&gt;
</PRE>